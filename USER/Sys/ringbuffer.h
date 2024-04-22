
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include "stdbool.h"
#include <stdio.h>

struct ring_buffer {
	unsigned short in;
	unsigned short out;
	unsigned short size;
	unsigned char *buf;
};

bool RingBufferInit(struct ring_buffer *ring_buffer_p, unsigned char *pool, unsigned short buf_size);
bool RingBufferEmpty(struct ring_buffer *ring_buffer_p);
bool RingBufferFull(struct ring_buffer *ring_buffer_p);
unsigned short GetRingBufferLen(struct ring_buffer *ring_buffer_p);
void RingBufferClear(struct ring_buffer *ring_buffer_p);
void RingBufferDel(struct ring_buffer *ring_buffer_p);
int RingBufferPut(struct ring_buffer *ring_buffer_p, unsigned char *buf, unsigned short len);
unsigned short RingBufferGet(struct ring_buffer *ring_buffer_p, unsigned char *buf, unsigned short buf_len);

#endif
