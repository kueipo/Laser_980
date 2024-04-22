#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include "GUI_Paint.h"
#include "ringbuffer.h"

#define CONSOLE_DEBUG    		1
#define CONSOLE_LOG_ERR			1
#define CONSOLE_LOG_INFO		1

#ifndef CONSOLE_DEBUG
	#define CONSOLE_DEBUG    0
#endif
#ifndef CSL_CONSOLE_LOG_PRINTF
	#ifdef RT_VER_NUM
		/* for RT-Thread platform */
		extern void rt_kprintf(const char *fmt, ...);
		#define CONSOLE_LOG_PRINTF rt_kprintf
	#else
		#define CONSOLE_LOG_PRINTF printf
	#endif /* RT_VER_NUM */
#endif /* CONSOLE_LOG_PRINTF */

#if CONSOLE_DEBUG
	#ifdef Console_Assert
		#undef Console_Assert
	#endif	/* Console_Assert */
	#define Console_Assert(EXPR)                                                   \
	if (!(EXPR))                                                                   \
	{                                                                              \
			CONSOLE_LOG_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);        \
			while (1);                                                                 \
	}
	/* debug level log */
	#ifdef  Console_log_d
		#undef  Console_log_d
	#endif	/* Console_log_d */
	#define Console_log_d(...)           CONSOLE_LOG_PRINTF("[D][CONSOLE] (%s:%d) ", __FUNCTION__, __LINE__);CONSOLE_LOG_PRINTF(__VA_ARGS__);CONSOLE_LOG_PRINTF("\n")
#else
	#ifdef Console_Assert
		#undef Console_Assert
	#endif	/* Console_Assert */
	#define Console_Assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  Console_log_d
		#undef  Console_log_d
	#endif	/* Console_log_d */
	#define Console_log_d(...)
#endif /* CONSOLE_DEBUG */

#ifndef CONSOLE_LOG_ERR
	#define CONSOLE_LOG_ERR    0
#endif
#if CONSOLE_LOG_ERR
	/* error level log */
	#ifdef  Console_log_err
		#undef  Console_log_err
	#endif
	#define Console_log_err(...)          CONSOLE_LOG_PRINTF("\033[31;22m[E][CONSOLE] (%s:%d) ", __FUNCTION__, __LINE__);CONSOLE_LOG_PRINTF(__VA_ARGS__);CONSOLE_LOG_PRINTF("\033[0m\n")
#else
	/* error level log */
	#ifdef  Console_log_err
		#undef  Console_log_err
	#endif
	#define Console_log_err(...)
#endif

#ifndef CONSOLE_LOG_INFO
	#define CONSOLE_LOG_INFO    0
#endif
#if CONSOLE_LOG_INFO
	/* info level log */
	#ifdef  Console_log_info
		#undef  Console_log_info
	#endif
	#define Console_log_info(...)         CONSOLE_LOG_PRINTF("\033[32;22m[I][CONSOLE] ");CONSOLE_LOG_PRINTF(__VA_ARGS__);CONSOLE_LOG_PRINTF("\033[0m\n")
#else
	/* info level log */
	#ifdef  Console_log_info
		#undef  Console_log_info
	#endif
	#define Console_log_info(...)
#endif

//================================================================================
#define	MAX_BUFF_SIZE		128
typedef struct{
	uint8_t head;
	uint8_t tail;
	uint8_t buf[MAX_BUFF_SIZE];
}RINGBUFFER_ST;

extern RINGBUFFER_ST RecBuff;

/* LED½á¹¹Ìå */
typedef struct {
    volatile uint8_t  cnt;
	volatile uint8_t  stat;
} LED_DEVICE;
extern LED_DEVICE Led;

void Console_Init(void);
void Console_Handle(void);
void Refresh_Time(void);
void Refresh_LaserCnt(void);
void Refresh_J(void);
void Refresh_HZ(void);
void Refresh_MS(void);
void Refresh_AllData(void);
void Heart_Beat(void);

#endif
