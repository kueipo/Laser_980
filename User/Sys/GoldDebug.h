#ifndef _GOLD_DEBUG_H
#define _GOLD_DEBUG_H

#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define GOL_DEBUG    		0
#define GOL_LOG_ERR			1
#define GOL_LOG_INFO		1


#ifndef GOL_DEBUG
#define GOL_DEBUG    0
#endif
#ifndef GOL_LOG_PRINTF
#ifdef RT_VER_NUM
/* for RT-Thread platform */
extern void rt_kprintf(const char *fmt, ...);
#define GOL_LOG_PRINTF rt_kprintf
#else
#define GOL_LOG_PRINTF printf
#endif /* RT_VER_NUM */
#endif /* GOL_LOG_PRINTF */

#if GOL_DEBUG
	#ifdef Gol_assert
		#undef Gol_assert
	#endif
	#define Gol_assert(EXPR)                                                           \
	if (!(EXPR))                                                                   \
	{                                                                              \
			GOL_LOG_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);        \
			while (1);                                                                 \
	}

	/* debug level log */
	#ifdef  Gol_log_d
		#undef  Gol_log_d
	#endif
	#define Gol_log_d(...)                     GOL_LOG_PRINTF("[D] (%s:%d) ", __FUNCTION__, __LINE__);           GOL_LOG_PRINTF(__VA_ARGS__);GOL_LOG_PRINTF("\n")

#else

	#ifdef Gol_assert
		#undef Gol_assert
	#endif
	#define Gol_assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  Gol_log_d
		#undef  Gol_log_d
	#endif
	#define Gol_log_d(...)
#endif /* GOL_DEBUG */

#ifndef GOL_LOG_ERR
#define GOL_LOG_ERR    0
#endif
#if GOL_LOG_ERR
	/* error level log */
	#ifdef  Gol_log_err
	#undef  Gol_log_err
	#endif
	#define Gol_log_err(...)                     GOL_LOG_PRINTF("\033[31;22m[E] (%s:%d) ", __FUNCTION__, __LINE__);GOL_LOG_PRINTF(__VA_ARGS__);GOL_LOG_PRINTF("\033[0m\n")
#else
	/* error level log */
	#ifdef  Gol_log_err
		#undef  Gol_log_err
	#endif
	#define Gol_log_err(...)
#endif

#ifndef GOL_LOG_INFO
#define GOL_LOG_INFO    0
#endif
#if GOL_LOG_INFO
	/* info level log */
	#ifdef  Gol_log_info
	#undef  Gol_log_info
	#endif
	#define Gol_log_info(...)                     GOL_LOG_PRINTF("\033[32;22m[I] ");                                GOL_LOG_PRINTF(__VA_ARGS__);GOL_LOG_PRINTF("\033[0m\n")
#else
	/* info level log */
	#ifdef  Gol_log_info
	#undef  Gol_log_info
	#endif
	#define Gol_log_info(...)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

/*
    在命令行下能产生五颜六色的字体和图案，只需要加上一些颜色代码，例如：
    printf(“\033[0;30;41m color!!! \033[0m Hello \n”);
　　其中41的位置代表字的背景色, 30的位置是代表字的颜色，0 是字的一些特殊属性，0代表默认关闭，一些其他属性如闪烁、下划线等。ascii code 是对颜色进行调用的。
    \033[ ; m …… \033[0m
　　颜色的控制通过ESC字符(\033)加”[“加颜色代码加”m”实现。ESC的ASCII码是十进制的27，八进制的033(\033)。

　　在 ANSI 兼容终端里，可以用彩色显示文本而不仅仅是黑白。但是我们自己编写的程序能否输出彩色的字符呢？当然答案是肯定的。下面的语句就输出高亮的黑色背景的绿色字。
　　printf(“\033[1;40;32m color!!! \033[0m hello\n”);
　　\033 声明了转义序列的开始，然后是 [ 开始定义颜色。后面的 1 定义了高亮显示字符。然后是背景颜色，这里面是40，表示黑色背景。接着是前景颜色，这里面是32，表示绿色。我们用 \033[0m 关闭转义序列， \033[0m 是终端默认颜色。通过上面的介绍，就知道了如何输出彩色字符了。

字色              背景              颜色
---------------------------------------
30                40              黑色
31                41              紅色
32                42              綠色
33                43              黃色
34                44              藍色
35                45              紫紅色
36                46              青藍色
37                47              白色

代码 意义
————————-
0 终端默认设置（黑底白字）
1 高亮显示
4 使用下划线
5 闪烁
7 反白显示
8 不可见

printf("\033[1;33m Hello World. \033[0m \n");  
颜色列表如下:  
none         = "\033[0m"  
black        = "\033[0;30m"  
dark_gray    = "\033[1;30m"  
blue         = "\033[0;34m"  
light_blue   = "\033[1;34m"  
green        = "\033[0;32m"  
light_green -= "\033[1;32m"  
cyan         = "\033[0;36m"  
light_cyan   = "\033[1;36m"  
red          = "\033[0;31m"  
light_red    = "\033[1;31m"  
purple       = "\033[0;35m"  
light_purple = "\033[1;35m"  
brown        = "\033[0;33m"  
yellow       = "\033[1;33m"  
light_gray   = "\033[0;37m"  
white        = "\033[1;37m"  

字背景颜色范围:40--49                   字颜色: 30--39  
40: 黑                         30: 黑  
41:红                          31: 红  
42:绿                          32: 绿  
43:黄                          33: 黄  
44:蓝                          34: 蓝  
45:紫                          35: 紫  
46:深绿                        36: 深绿  
47:白色                        37: 白色  



输出特效格式控制：  

\033[0m  关闭所有属性    
\033[1m   设置高亮度    
\03[4m   下划线    
\033[5m   闪烁    
\033[7m   反显    
\033[8m   消隐    
\033[30m   --   \033[37m   设置前景色    
\033[40m   --   \033[47m   设置背景色  



光标位置等的格式控制：  

\033[nA  光标上移n行    
\03[nB   光标下移n行    
\033[nC   光标右移n行    
\033[nD   光标左移n行    
\033[y;xH设置光标位置    
\033[2J   清屏    
\033[K   清除从光标到行尾的内容    
\033[s   保存光标位置    
\033[u   恢复光标位置    
\033[?25l   隐藏光标    
\33[?25h   显示光标

*/
