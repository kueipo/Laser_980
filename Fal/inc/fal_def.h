/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_DEF_H_
#define _FAL_DEF_H_

#include <stdint.h>
#include <stdio.h>
#include "fal/porting/fal_cfg.h"

#define FAL_SW_VERSION                 "0.5.99"

#ifndef FAL_MALLOC
#define FAL_MALLOC                     malloc
#endif

#ifndef FAL_CALLOC
#define FAL_CALLOC                     calloc
#endif

#ifndef FAL_REALLOC
#define FAL_REALLOC                    realloc
#endif

#ifndef FAL_FREE
#define FAL_FREE                       free
#endif

#ifndef FAL_DEBUG
#define FAL_DEBUG                      0
#endif

#ifndef FAL_PRINTF
	#ifdef RT_VER_NUM
		/* for RT-Thread platform */
		extern void rt_kprintf(const char *fmt, ...);
		#define FAL_PRINTF rt_kprintf
	#else
		#define FAL_PRINTF printf
	#endif /* RT_VER_NUM */
#endif /* FAL_PRINTF */

#if FAL_DEBUG
	#ifdef fal_assert
		#undef fal_assert
	#endif
	#define fal_assert(EXPR)                                                \
		if (!(EXPR))                                                          \
		{                                                                     \
			FAL_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__); \
			while (1)                                                           \
				;                                                                 \
		}

	/* debug level log */
	#ifdef fal_log_d
		#undef fal_log_d
	#endif
	#define fal_log_d(...)                                     \
		FAL_PRINTF("[D][FAL] (%s:%d) ", __FUNCTION__, __LINE__); \
		FAL_PRINTF(__VA_ARGS__);                                 \
		FAL_PRINTF("\n")

#else

	#ifdef fal_assert
		#undef fal_assert
	#endif
	#define fal_assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  fal_log_d
		#undef  fal_log_d
	#endif
	#define fal_log_d(...)
#endif /* FAL_DEBUG */

#if FAL_LOG_ERR
/* error level log */
#ifdef fal_log_err
#undef fal_log_err
#endif
#define fal_log_err(...)                                              \
	FAL_PRINTF("\033[31;22m[E][FAL] (%s:%d) ", __FUNCTION__, __LINE__); \
	FAL_PRINTF(__VA_ARGS__);                                            \
	FAL_PRINTF("\033[0m\n")
#else
	#define fal_log_err(...) 
#endif

#if FAL_LOG_INFO
	/* info level log */
	#ifdef fal_log_i
		#undef fal_log_i
	#endif
	#define fal_log_i(...)                \
		FAL_PRINTF("\033[32;22m[I][FAL] "); \
		FAL_PRINTF(__VA_ARGS__);            \
		FAL_PRINTF("\033[0m\n")
	#else
		#define fal_log_i(...) 
#endif

/* FAL flash and partition device name max length */
#ifndef FAL_DEV_NAME_MAX
	#define FAL_DEV_NAME_MAX 12
#endif

struct fal_flash_dev
{
	char name[FAL_DEV_NAME_MAX];

	/* flash device start address and len  */
	uint32_t addr;
	size_t len;
	/* the block size in the flash for erase minimum granularity */
	size_t blk_size;

	struct
	{
		int (*init)(void);
		int (*read)(long offset, uint8_t *buf, size_t size);
		int (*write)(long offset, const uint8_t *buf, size_t size);
		int (*erase)(long offset, size_t size);
	} ops;

	/* write minimum granularity, unit: bit.
		 1(nor flash)/ 8(stm32f2/f4)/ 32(stm32f1)/ 64(stm32l4)
		 0 will not take effect. */
	size_t write_gran;
};
typedef struct fal_flash_dev *fal_flash_dev_t;

/**
 * FAL partition
 */
struct fal_partition
{
	uint32_t magic_word;

	/* partition name */
	char name[FAL_DEV_NAME_MAX];
	/* flash device name for partition */
	char flash_name[FAL_DEV_NAME_MAX];

	/* partition offset address on flash device */
	long offset;
	size_t len;

	uint32_t reserved;
};
typedef struct fal_partition *fal_partition_t;

#endif /* _FAL_DEF_H_ */