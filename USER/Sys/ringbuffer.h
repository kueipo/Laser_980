
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include "stdbool.h"

struct ring_buffer {
	unsigned int in; /*写指针*/
	unsigned int out; /*读指针*/
	unsigned int size;  /*环形缓冲区大小*/
	unsigned char *buf; /*环形缓冲区*/
};

bool RingBufferInit(struct ring_buffer *ring_buffer_p, unsigned char *pool, unsigned int buf_size);
bool RingBufferEmpty(struct ring_buffer *ring_buffer_p);
bool RingBufferFull(struct ring_buffer *ring_buffer_p);
unsigned int GetRingBufferLen(struct ring_buffer *ring_buffer_p);
void RingBufferClear(struct ring_buffer *ring_buffer_p);
void RingBufferDel(struct ring_buffer *ring_buffer_p);
int RingBufferPut(struct ring_buffer *ring_buffer_p, unsigned char *buf, unsigned int len);
unsigned int RingBufferGet(struct ring_buffer *ring_buffer_p, unsigned char *buf, unsigned int buf_len);

#endif
