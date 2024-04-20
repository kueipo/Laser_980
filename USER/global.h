#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

//typedef unsigned char                   BOOL;
//typedef signed char                     S8;
//typedef unsigned char                   U8;
//typedef signed short                    S16;
//typedef unsigned short                  U16;
//typedef signed int                      S32;
//typedef unsigned int                    U32;
//typedef signed long long int            S64;
//typedef unsigned long long int          U64;
//typedef float                           F32;
//typedef double                          F64;

#ifndef  PACKED_STRUCT
	#define PACKED_STRUCT __packed typedef struct
#endif

//#ifndef  _false
//	#define  _false	0
//#endif

//#ifndef  _true
//	#define  _true	1
//#endif

#ifndef NULL
	#define NULL 	 (void *)0
#endif

#ifndef _INLINE_
	#define _INLINE_ __inline
#endif

#ifndef PNULL
	#define PNULL (void *)0
#endif

//#ifndef TRUE
//  #define TRUE (BOOL)(1)
//#endif

//#ifndef FALSE
//  #define FALSE (BOOL)(0)
//#endif

/* Bit defined */
#define BIT0			(0x01)
#define BIT1			(0x02)
#define BIT2			(0x04)
#define BIT3			(0x08)
#define BIT4			(0x10)
#define BIT5			(0x20)
#define BIT6			(0x40)
#define BIT7			(0x80)
#define BIT8			(0x100)
#define BIT9			(0x200)
#define BIT10			(0x400)
#define BIT11			(0x800)
#define BIT12			(0x1000)
#define BIT13			(0x2000)
#define BIT14			(0x4000)
#define BIT15			(0x8000)

/* Bit defined */
#define BIT_0			(0x01)
#define BIT_1			(0x02)
#define BIT_2			(0x04)
#define BIT_3			(0x08)
#define BIT_4			(0x10)
#define BIT_5			(0x20)
#define BIT_6			(0x40)
#define BIT_7			(0x80)

///********************  Task Layer  *******************/

#ifndef MAX
	#define MAX(a, b)    ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
	#define MIN(a, b)    ((a) > (b) ? (b) : (a))
#endif

/* ABSoulute value */
#ifndef ABS_RETURN
#define ABS_RETURN(x,y)               ((x) < (y)) ? ((y)-(x)) : ((x)-(y))
#endif

//#define SHIELD_WARNING(a) ((a) = (a))
#define SHIELD_WARNING(a) ((void)(a))

#ifndef SET_BIT
	#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#endif

#ifndef CLEAR_BIT
	#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#endif

#ifndef READ_BIT
	#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#endif

#ifndef CLEAR_REG
	#define CLEAR_REG(REG)        ((REG) = (0x0))
#endif

#ifndef WRITE_REG
	#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#endif

#ifndef READ_REG
	#define READ_REG(REG)         ((REG))
#endif


#ifndef ENABLE_IRQ
	#define ENABLE_IRQ()         __enable_irq()
#endif

#ifndef DISABLE_IRQ
	#define DISABLE_IRQ()        __disable_irq()
#endif

#ifndef NOP
	#define NOP()                  __NOP()
#endif

#ifndef SYSTEM_RESET
	#define SYSTEM_RESET()       NVIC_SystemReset()
#endif



/*
 * \brief   Typecast the macro argument into milliseconds
 */
#define TmrMilliseconds( n )    ( (uint32_t) (n) * 1 )
   
    
/*
 * \brief   Converts the macro argument from seconds to Milliseconds
 */
#define TmrSecondsToMilliseconds( n )   ( (uint32_t) ((n) * 1000) )

/*
 * \brief   Converts the macro argument from microseconds to seconds
 */
#define TmrMicrosecondsToSeconds( n )   ( ((n) + 500000) / 1000000 )

/*
 * \brief   Converts the macro argument (i.e. seconds) into milliseconds
 */
#define TmrSeconds( n )         ( (uint32_t) (TmrMilliseconds(n) * 1000) )

/*
 * \brief   Converts the macro argument (i.e. minutes) into milliseconds
 */
#define TmrMinutes( n )         ( (uint32_t) (TmrSeconds(n) * 60) )

/* Compute the number of elements of an array */
#define NumberOfElements(x)     (sizeof(x)/sizeof((x)[0]))

/* Compute the size of a string initialized with quotation marks */
#define SizeOfString(string)    (sizeof(string) - 1)

#define GetRelAddr(strct, member) ((uint32_t)&(((strct*)(void *)0)->member))
#define GetSizeOfMember(strct, member) sizeof(((strct*)(void *)0)->member)

#define BigtoLittle16(A)              (( ((uint16_t)(A) & 0xff00) >> 8)| (( (U16)(A) & 0x00ff) << 8))  


#define BigtoLittle32(A)              ((( (uint32_t)(A) & 0xff000000) >> 24) | \
                                       (( (uint32_t)(A) & 0x00ff0000) >> 8)   | \
                                       (( (uint32_t)(A) & 0x0000ff00) << 8)   | \
                                       (( (uint32_t)(A) & 0x000000ff) << 24))  
 

#endif



