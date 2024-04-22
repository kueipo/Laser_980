
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Define --------------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  BSP Init
 * @param  None
 * @retval None
 */
void BSP_Init(void)
{
#if 0
  HAL_Init();
    
  /* Init Clock */
  DISABLE_IRQ();    
  SystemClock_Config(); 
  ENABLE_IRQ();
#endif

#if 0
	Max5400_Init();
#else
//	AD840X_Init();
#endif
//  BSP_Key_Init();
//	BSP_Pump_Init();
//	BSP_Water_Init();
	BSP_Adc_Init();
//	BSP_Cooler_Init();
//	BSP_Frequency_Init();
//	BSP_Power_Init();
	BSP_Uart_Init();
//	BSP_Motor_Init();
//	BSP_SafeLocker_Init();
//	BSP_Handpiece_Init();
//  BSP_Led_Init();
	BSP_Laser_Init();
	/* add task here */
}


#define PRINTF_PORT &huart2
#if 1/* 半主机模式 */
	#include "stdio.h"
	#pragma import(__use_no_semihosting)  // 确保没有从 C 库链接使用半主机的函数
	void _sys_exit(int  x) //定义 _sys_exit() 以避免使用半主机模式
	{
		x = x;
	}
	struct __FILE  // 标准库需要的支持函数
	{
		int handle;
	};
	/* FILE is typedef ’ d in stdio.h. */
	FILE __stdout;
	int fputc(int ch, FILE *f){
		HAL_UART_Transmit(PRINTF_PORT, (uint8_t *)&ch, 1, 0xFFFF);
		return ch;
	}
#else
  /* 使用MicroLIB库 */
	// 添加的代码如下，进行函数重构
	#ifdef __GNUC__            //gcc编译器宏定义
		/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
	 set to 'Yes') calls __io_putchar() */
			#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#else
			#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#endif /* __GNUC__ */

	/*上面的意思是：
	如果定义了宏__GNUC__，即使用GCC编译器，则定义宏#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	如果没有定义宏__GNUC__，即不使用GCC编译器，则定义宏#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)  */

	//添加printf重构函数的实现部分
	PUTCHAR_PROTOTYPE
	{
		HAL_UART_Transmit(PRINTF_PORT, (uint8_t *)&ch, 1, 0xFFFF);
		return ch;
	}
#endif
