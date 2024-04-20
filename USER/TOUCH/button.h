#ifndef __BUTTON_H_
#define __BUTTON_H_

#include <stdint.h>

#define BTN_DEBUG    		0
#define BTN_LOG_ERR			1
#define BTN_LOG_INFO		0


#ifndef BTN_DEBUG
#define BTN_DEBUG    0
#endif

#ifndef LOG_PRINTF
#ifdef RT_VER_NUM
/* for RT-Thread platform */
extern void rt_kprintf(const char *fmt, ...);
#define LOG_PRINTF rt_kprintf
#else
#define LOG_PRINTF printf
#endif /* RT_VER_NUM */
#endif /* LOG_PRINTF */

#if BTN_DEBUG
	#ifdef Btn_assert
		#undef Btn_assert
	#endif
	#define Btn_assert(EXPR)                                                           \
	if (!(EXPR))                                                                   \
	{                                                                              \
			LOG_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);        \
			while (1);                                                                 \
	}
	/* debug level log */
	#ifdef  Btn_log_d
		#undef  Btn_log_d
	#endif
	#define Btn_log_d(...)           LOG_PRINTF("[D][BTN] (%s:%d) ", __FUNCTION__, __LINE__);LOG_PRINTF(__VA_ARGS__);LOG_PRINTF("\n")
#else
	#ifdef Btn_assert
		#undef Btn_assert
	#endif
	#define Btn_assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  Btn_log_d
		#undef  Btn_log_d
	#endif
	#define Btn_log_d(...)
#endif /* BTN_DEBUG */

#ifndef BTN_LOG_ERR
	#define BTN_LOG_ERR    0
#endif
#if BTN_LOG_ERR
	/* error level log */
	#ifdef  Btn_log_err
	#undef  Btn_log_err
	#endif
	#define Btn_log_err(...)          LOG_PRINTF("\033[31;22m[E][BTN] (%s:%d) ", __FUNCTION__, __LINE__);LOG_PRINTF(__VA_ARGS__);LOG_PRINTF("\033[0m\n")
#else
	/* error level log */
	#ifdef  Btn_log_err
	#undef  Btn_log_err
	#endif
	#define Btn_log_err(...)
#endif

#ifndef BTN_LOG_INFO
	#define BTN_LOG_INFO    0
#endif
#if BTN_LOG_INFO
	/* info level log */
	#ifdef  Btn_log_info
	#undef  Btn_log_info
	#endif
	#define Btn_log_info(...)         LOG_PRINTF("\033[32;22m[I][BTN] ");LOG_PRINTF(__VA_ARGS__);LOG_PRINTF("\033[0m\n")
#else
	/* info level log */
	#ifdef  Btn_log_info
	#undef  Btn_log_info
	#endif
	#define Btn_log_info(...)
#endif

/* UI页面序号 */
enum UI_IDX{
	MAIN = 0,
	OPERATION_1,
	OPERATION_2,
	OPERATION_3,
	PAGETOTAL,
};

/* 按键序号 */
enum {
	BUTTON_0 = 0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_TOLAL,
};

/* 按键区域块 */
typedef struct {
    volatile uint16_t x1;
    volatile uint16_t y1;
    volatile uint16_t x2;
    volatile uint16_t y2;
} BUTTON_X_Y;

/* 按键结构体 */
typedef struct {
    volatile enum UI_IDX  ui_idx;
    volatile uint8_t  btn_idx;
	volatile BUTTON_X_Y  btn[PAGETOTAL][BUTTON_TOLAL];
	volatile uint8_t	app_idx[PAGETOTAL][BUTTON_TOLAL];
} BUTTON_STRUCT;

extern BUTTON_STRUCT Button;

void Send_Data(unsigned char *data,unsigned char size);

#endif
