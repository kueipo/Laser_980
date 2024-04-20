#include "Sys/Delay.h"

#if 0
	#include "stm32f0xx_hal.h"
#endif
#if defined(STM32F103xE)
	#include "stm32f1xx_hal.h"
#endif

/* 如果使用ucos,则包括下面的头文件即可. */
#if SYSTEM_SUPPORT_OS
	/* ucos 使用 */
	#include "includes.h"			  
#endif

/* us延时倍乘数 */
static unsigned long int fac_us = 0;			

#if SYSTEM_SUPPORT_OS
	/* ms延时倍乘数,在os下,代表每个节拍的ms数 */
	static unsigned int fac_m s= 0;
#endif

/* 如果SYSTEM_SUPPORT_OS定义了,说明要支持OS了(不限于UCOS). */
#if SYSTEM_SUPPORT_OS
/**
* 当delay_us/delay_ms需要支持OS的时候需要三个与OS相关的宏定义和函数来支持
* 首先是3个宏定义:
* delay_osrunning:用于表示OS当前是否正在运行,以决定是否可以使用相关函数
* delay_ostickspersec:用于表示OS设定的时钟节拍,delay_init将根据这个参数来初始哈systick
* delay_osintnesting:用于表示OS中断嵌套级别,因为中断里面不可以调度,delay_ms使用该参数来决定如何运行
* 然后是3个函数:
* delay_osschedlock:用于锁定OS任务调度,禁止调度
* delay_osschedunlock:用于解锁OS任务调度,重新开启调度
* delay_ostimedly:用于OS延时,可以引起任务调度.
*/

/**
* 本例程仅作UCOSII和UCOSIII的支持,其他OS,请自行参考着移植
* 支持UCOSII
*/
/* OS_CRITICAL_METHOD定义了,说明要支持UCOSII */
#ifdef 	OS_CRITICAL_METHOD
	/* OS是否运行标记,0,不运行;1,在运行 */						
	#define delay_osrunning		OSRunning
	/* OS时钟节拍,即每秒调度次数 */	
	#define delay_ostickspersec	OS_TICKS_PER_SEC
	/* 中断嵌套级别,即中断嵌套次数 */
	#define delay_osintnesting	OSIntNesting
#endif

/**
* 支持UCOSIII
*/
/* CPU_CFG_CRITICAL_METHOD定义了,说明要支持UCOSIII */
#ifdef 	CPU_CFG_CRITICAL_METHOD
	/* OS是否运行标记,0,不运行;1,在运行 */
	#define delay_osrunning		OSRunning
	/* OS时钟节拍,即每秒调度次数 */
	#define delay_ostickspersec	OSCfg_TickRate_Hz
	/* 中断嵌套级别,即中断嵌套次数 */
	#define delay_osintnesting 	OSIntNestingCtr
#endif


/**
* us级延时时,关闭任务调度(防止打断us级延迟)
*/
void delay_osschedlock(void)
{
/* 使用UCOSIII */
#ifdef CPU_CFG_CRITICAL_METHOD
	OS_ERR err;
	/* UCOSIII的方式,禁止调度，防止打断us延时 */
	OSSchedLock(&err);
/* 否则UCOSII */
#else
	/* UCOSII的方式,禁止调度，防止打断us延时 */
	OSSchedLock();
#endif
}

/**
* us级延时时,恢复任务调度
*/
void delay_osschedunlock(void)
{
/* 使用UCOSIII */
#ifdef CPU_CFG_CRITICAL_METHOD
	OS_ERR err;
	/* UCOSIII的方式,恢复调度 */
	OSSchedUnlock(&err);
/* 否则UCOSII */
#else
	/* UCOSII的方式,恢复调度 */
	OSSchedUnlock();
#endif
}

/**
* 调用OS自带的延时函数延时
* ticks:延时的节拍数
*/
void delay_ostimedly(unsigned long int ticks)
{
#ifdef CPU_CFG_CRITICAL_METHOD
	OS_ERR err;
	/* UCOSIII延时采用周期模式 */
	OSTimeDly(ticks, OS_OPT_TIME_PERIODIC, &err);
#else
	/* UCOSII延时 */
	OSTimeDly(ticks);
#endif
}

/**
* systick中断服务函数,使用OS时用到
*/
void SysTick_Handler(void)
{
	HAL_IncTick();
	/* OS开始跑了,才执行正常的调度处理 */
	if (delay_osrunning == 1)
	{
		/* 进入中断 */
		OSIntEnter();
		/* 调用ucos的时钟服务程序 */
		OSTimeTick();
		/* 触发任务切换软中断 */
		OSIntExit();
	}
}
#endif

/**			   
* 初始化延迟函数
* 当使用ucos的时候,此函数会初始化ucos的时钟节拍
* SYSTICK的时钟固定为AHB时钟
* SYSCLK:系统时钟频率
*/
void delay_init(unsigned char SYSCLK)
{
/* 如果需要支持OS. */
#if SYSTEM_SUPPORT_OS
	unsigned long int reload;
#endif
	/* SysTick频率为HCLK */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	/* 不论是否使用OS,fac_us都需要使用 */
	fac_us = SYSCLK;
	/* 如果需要支持OS. */
#if SYSTEM_SUPPORT_OS
	/* 每秒钟的计数次数 单位为K */
	reload = SYSCLK;
	/* 根据delay_ostickspersec设定溢出时间 */
	reload *= 1000000 / delay_ostickspersec;
	/* reload为24位寄存器,最大值:16777216,在180M下,约合0.745s左右 */
	/* 代表OS可以延时的最少单位 */
	fac_ms = 1000 / delay_ostickspersec;
	/* 开启SYSTICK中断 */
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	/* 每1/OS_TICKS_PER_SEC秒中断一次 */
	SysTick->LOAD = reload;
	/* 开启SYSTICK */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#else
#endif
}

/* 如果需要支持OS. */
#if SYSTEM_SUPPORT_OS 

/**
* 延时nus
* nus:要延时的us数.	
* nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)
*/
void delay_us(unsigned long int nus)
{
	unsigned long int ticks;
	unsigned long int told, tnow, tcnt = 0;
	/* LOAD的值 */
	unsigned long int reload = SysTick->LOAD;
	/* 需要的节拍数 */
	ticks = nus * fac_us;
	/* 阻止OS调度，防止打断us延时 */
	delay_osschedlock();
	/* 刚进入时的计数器值 */
	told = SysTick->VAL;
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
			{
				/* 这里注意一下SYSTICK是一个递减的计数器就可以了. */
				tcnt += told - tnow;
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if (tcnt >= ticks)
			{
				/* 时间超过/等于要延迟的时间,则退出. */
				break;
			}
		}
	}
	/* 恢复OS调度 */
	delay_osschedunlock();
}
/**
* 延时nms
* nms:要延时的ms数
* nms:0~65535
*/
void delay_ms(unsigned int nms)
{
	/* 如果OS已经在跑了,并且不是在中断里面(中断里面不能任务调度) */
	if (delay_osrunning && delay_osintnesting == 0)
	{
		/* 延时的时间大于OS的最少时间周期 */
		if (nms >= fac_ms)
		{
			/* OS延时 */
			delay_ostimedly(nms / fac_ms);
		}
		/* OS已经无法提供这么小的延时了,采用普通方式延时 */
		nms %= fac_ms;
	}
	/* 普通方式延时 */
	delay_us((unsigned long int)(nms * 1000));
}

/* 不用ucos时 */
#else

/**
* 延时nus
* nus为要延时的us数.
* nus:0~190887435(最大值即2^32/fac_us@fac_us=22.5)
*/
void delay_us(unsigned long int nus)
{
	unsigned long int ticks;
	unsigned long int told, tnow, tcnt = 0;
	/* LOAD的值 */
	unsigned long int reload = SysTick->LOAD;
	/* 需要的节拍数 */
	ticks = nus * fac_us;
	/* 刚进入时的计数器值 */
	told = SysTick->VAL;
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
			{
				/* 这里注意一下SYSTICK是一个递减的计数器就可以了. */
				tcnt += told - tnow;
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if (tcnt >= ticks)
			{
				/* 时间超过/等于要延迟的时间,则退出. */
				break;
			}
		}
	};
}

/**
* 延时nms
* nms:要延时的ms数
*/
void delay_ms(unsigned int nms)
{
	unsigned int i;
	for (i = 0; i < nms; i++)
	{
		delay_us(1000);
	}
}

#endif
