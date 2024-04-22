/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef RINGBUFFER_H__
#define RINGBUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "GoldDebug.h"

#define RB_DEBUG	0

#ifndef RB_DEBUG
#define RB_DEBUG    0
#endif

#ifndef RB_PRINTF
    #ifdef RT_VER_NUM
        /* for RT-Thread platform */
        extern void rt_kprintf(const char *fmt, ...);
        #define RB_PRINTF rt_kprintf
    #else
        #define RB_PRINTF printf
    #endif /* RT_VER_NUM */
#endif /* RB_PRINTF */

#if RB_DEBUG
	#ifdef Rb_assert
		#undef Rb_assert
	#endif
	#define Rb_assert(EXPR)                                                         \
		if (!(EXPR))                                                                \
		{                                                                           \
			RB_PRINTF("[RB](%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);  \
			while (1);                                                              \
		}

	/* debug level log */
	#ifdef  Rb_log_d
		#undef  Rb_log_d
	#endif
	#define Rb_log_d(...)                     RB_PRINTF("[D/RB] (%s:%d) ", __FUNCTION__, __LINE__);RB_PRINTF(__VA_ARGS__);RB_PRINTF("\n")

#else
	#ifdef Rb_assert
		#undef Rb_assert
	#endif
	#define Rb_assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  Rb_log_d
		#undef  Rb_log_d
	#endif
	#define Rb_log_d(...)
#endif /* FAL_DEBUG */
		
/* ring buffer */
struct ringbuffer
{
    uint8_t *buffer_ptr;
    /* use the msb of the {read,write}_index as mirror bit. You can see this as
     * if the buffer adds a virtual mirror and the pointers point either to the
     * normal or to the mirrored buffer. If the write_index has the same value
     * with the read_index, but in a different mirror, the buffer is full.
     * While if the write_index and the read_index are the same and within the
     * same mirror, the buffer is empty. The ASCII art of the ringbuffer is:
     *
     *          mirror = 0                    mirror = 1
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Full
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     *  read_idx-^                   write_idx-^
     *
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Empty
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * read_idx-^ ^-write_idx
     *
     * The tradeoff is we could only use 32KiB of buffer for 16 bit of index.
     * But it should be enough for most of the cases.
     *
     * Ref: http://en.wikipedia.org/wiki/Circular_buffer#Mirroring */
    uint16_t read_mirror : 1;
    uint16_t read_index : 15;
    uint16_t write_mirror : 1;
    uint16_t write_index : 15;
    /* as we use msb of index as mirror bit, the size should be signed and
     * could only be positive. */
    int16_t buffer_size;
};

enum ringbuffer_state
{
    RINGBUFFER_EMPTY,
    RINGBUFFER_FULL,
    /* half full is neither full nor empty */
    RINGBUFFER_HALFFULL,
};

/**
 * RingBuffer for DeviceDriver
 *
 * Please note that the ring buffer implementation of RT-Thread
 * has no thread wait or resume feature.
 */
void ringbuffer_init(struct ringbuffer *rb, uint8_t *pool, int16_t size);
void ringbuffer_reset(struct ringbuffer *rb);
uint16_t ringbuffer_put(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_put_force(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_putchar(struct ringbuffer *rb, const uint8_t ch);
uint16_t ringbuffer_putchar_force(struct ringbuffer *rb, const uint8_t ch);
uint16_t ringbuffer_get(struct ringbuffer *rb, uint8_t *ptr, uint16_t length);
uint16_t ringbuffer_getchar(struct ringbuffer *rb, uint8_t *ch);
uint16_t ringbuffer_data_len(struct ringbuffer *rb);

static __inline uint16_t ringbuffer_get_size(struct ringbuffer *rb)
{
    Rb_assert(rb != NULL);
    return rb->buffer_size;
}

/** return the size of empty space in rb */
#define ringbuffer_space_len(rb) ((rb)->buffer_size - ringbuffer_data_len(rb))

#ifdef __cplusplus
}
#endif

#endif
