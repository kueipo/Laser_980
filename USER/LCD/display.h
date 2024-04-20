#ifndef __DISPLAY_H
#define __DISPLAY_H	

#include <stdbool.h>
#include <stdint.h>
#include <fal.h>
#include "fonts.h"
#include "DEV_Config.h"

#define DSY_DEBUG    		0
#define DSY_LOG_ERR			1
#define DSY_LOG_INFO		0


#ifndef DSY_DEBUG
#define DSY_DEBUG    0
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

#if DSY_DEBUG
	#ifdef Dsy_assert
		#undef Dsy_assert
	#endif
	#define Dsy_assert(EXPR)                                                           \
	if (!(EXPR))                                                                   \
	{                                                                              \
			LOG_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);        \
			while (1);                                                                 \
	}
	/* debug level log */
	#ifdef  Dsy_log_d
		#undef  Dsy_log_d
	#endif
	#define Dsy_log_d(...)           LOG_PRINTF("[D][DSY] (%s:%d) ", __FUNCTION__, __LINE__);LOG_PRINTF(__VA_ARGS__);LOG_PRINTF("\n")
#else
	#ifdef Dsy_assert
		#undef Dsy_assert
	#endif
	#define Dsy_assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  Dsy_log_d
		#undef  Dsy_log_d
	#endif
	#define Dsy_log_d(...)
#endif /* DSY_DEBUG */

#ifndef DSY_LOG_ERR
	#define DSY_LOG_ERR    0
#endif
#if DSY_LOG_ERR
	/* error level log */
	#ifdef  Dsy_log_err
	#undef  Dsy_log_err
	#endif
	#define Dsy_log_err(...)          LOG_PRINTF("\033[31;22m[E][DSY] (%s:%d) ", __FUNCTION__, __LINE__);LOG_PRINTF(__VA_ARGS__);LOG_PRINTF("\033[0m\n")
#else
	/* error level log */
	#ifdef  Dsy_log_err
		#undef  Dsy_log_err
	#endif
	#define Dsy_log_err(...) 
#endif

#ifndef DSY_LOG_INFO
	#define DSY_LOG_INFO    0
#endif
#if DSY_LOG_INFO
	/* info level log */
	#ifdef  Dsy_log_info
	#undef  Dsy_log_info
	#endif
	#define Dsy_log_info(...)         LOG_PRINTF("\033[32;22m[I][DSY] ");LOG_PRINTF(__VA_ARGS__);LOG_PRINTF("\033[0m\n")
#else
	/* info level log */
	#ifdef  Dsy_log_info
	#undef  Dsy_log_info
	#endif
	#define Dsy_log_info(...)  
#endif


void ImageDisplay(const struct fal_partition *part, uint16_t xStart, uint16_t yStart);
void Char_Display(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char, sFONT* Font, UWORD Color_Background, UWORD Color_Foreground);
#endif
