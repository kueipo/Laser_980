/*****************************************************************************
* | File      	:	LCD_Test.h
* | Author      :   Waveshare team
* | Function    :   LCD test Demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-06-09
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _EPD_TEST_H_
#define _EPD_TEST_H_

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "Debug.h"
#include <stdlib.h> // malloc() free()

void LCD_0in96_test(void);

void LCD_1in14_test(void);

void LCD_1in3_test(void);

void LCD_1in54_test(void);

void LCD_1in8_test(void);

void LCD_2in_test(void);

void LCD_2in4_test(void);


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define LCD_DEBUG    		0
#define LCD_LOG_ERR			1
#define LCD_LOG_INFO		0

#ifndef LCD_DEBUG
#define LCD_DEBUG    0
#endif

#ifndef LCD_LOG_PRINTF
#ifdef RT_VER_NUM
/* for RT-Thread platform */
extern void rt_kprintf(const char *fmt, ...);
#define LCD_LOG_PRINTF rt_kprintf
#else
#define LCD_LOG_PRINTF printf
#endif /* RT_VER_NUM */
#endif /* LCD_LOG_PRINTF */

#if LCD_DEBUG
	#ifdef LCD_assert
		#undef LCD_assert
	#endif
	#define LCD_assert(EXPR)                                                           \
	if (!(EXPR))                                                                   \
	{                                                                              \
			LCD_LOG_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);        \
			while (1);                                                                 \
	}
	/* debug level log */
	#ifdef  LCD_log_d
		#undef  LCD_log_d
	#endif
	#define LCD_log_d(...)           LCD_LOG_PRINTF("[D][LCD] (%s:%d) ", __FUNCTION__, __LINE__);LCD_LOG_PRINTF(__VA_ARGS__);LCD_LOG_PRINTF("\n")
#else
	#ifdef LCD_assert
		#undef LCD_assert
	#endif
	#define LCD_assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  LCD_log_d
		#undef  LCD_log_d
	#endif
	#define LCD_log_d(...)
#endif /* LCD_DEBUG */

#ifndef LCD_LOG_ERR
	#define LCD_LOG_ERR    0
#endif
#if LCD_LOG_ERR
	/* error level log */
	#ifdef  LCD_log_err
		#undef  LCD_log_err
	#endif
	#define LCD_log_err(...)          LCD_LOG_PRINTF("\033[31;22m[E][LCD] (%s:%d) ", __FUNCTION__, __LINE__);LCD_LOG_PRINTF(__VA_ARGS__);LCD_LOG_PRINTF("\033[0m\n")
#else
	/* error level log */
	#ifdef  LCD_log_err
		#undef  LCD_log_err
	#endif
	#define LCD_log_err(...)
#endif

#ifndef LCD_LOG_INFO
	#define LCD_LOG_INFO    0
#endif
#if LCD_LOG_INFO
	/* info level log */
	#ifdef  LCD_log_info
		#undef  LCD_log_info
	#endif
	#define LCD_log_info(...)         LCD_LOG_PRINTF("\033[32;22m[I][LCD] ");LCD_LOG_PRINTF(__VA_ARGS__);LCD_LOG_PRINTF("\033[0m\n")
#else
	#ifdef  LCD_log_info
		#undef  LCD_log_info
	#endif
	#define LCD_log_info(...)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
