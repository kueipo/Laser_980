
#include "ringbuffer.h"

bool RingBufferInit(struct ring_buffer *ring_buffer_p, unsigned char *pool, unsigned short buf_size)
{
	if (ring_buffer_p == NULL)
		return false;
	
	ring_buffer_p->buf = pool;
	ring_buffer_p->size = buf_size;
	ring_buffer_p->in = 0;
	ring_buffer_p->out = 0;
	return true;
}

bool RingBufferEmpty(struct ring_buffer *ring_buffer_p)
{
	if (ring_buffer_p == NULL)
		return false;
	return (ring_buffer_p->in == ring_buffer_p->out);
}

bool RingBufferFull(struct ring_buffer *ring_buffer_p)
{
	if (ring_buffer_p == NULL)
		return false;
	return (((ring_buffer_p->in) % ring_buffer_p->size) == ring_buffer_p->out);
}

unsigned short GetRingBufferLen(struct ring_buffer *ring_buffer_p)
{
	if (ring_buffer_p)
		return ((ring_buffer_p->size - ring_buffer_p->out + ring_buffer_p->in) % ring_buffer_p->size);
	else
		return 0;
}

void RingBufferClear(struct ring_buffer *ring_buffer_p)
{
	if (ring_buffer_p == NULL)
		return;
		
	ring_buffer_p->in = 0;
	ring_buffer_p->out = 0;
}

void RingBufferDel(struct ring_buffer *ring_buffer_p)
{
	if (ring_buffer_p == NULL)
		return;
		
	ring_buffer_p->in = 0;
	ring_buffer_p->out = 0;
	ring_buffer_p->size = 0;
}

int RingBufferPut(struct ring_buffer *ring_buffer_p, unsigned char *buf, unsigned short len)
{
	unsigned short real_in_len = 0, i = 0, surplus_buf_len = 0;
	
	if (ring_buffer_p == NULL)
		return -1;

	if (len >= ring_buffer_p->size)
	{
		return -1;
	}

	surplus_buf_len = ring_buffer_p->size - GetRingBufferLen(ring_buffer_p);
	if (len > surplus_buf_len)
	{
		real_in_len = surplus_buf_len;
	}
	else if (len <= surplus_buf_len)
	{
		real_in_len = len;
	}

	for (i = 0; i < real_in_len; i++)
	{
		ring_buffer_p->buf[ring_buffer_p->in] = buf[i];
		ring_buffer_p->in = (ring_buffer_p->in + 1) % ring_buffer_p->size;
	}

	return i;
}

unsigned short RingBufferGet(struct ring_buffer *ring_buffer_p, unsigned char *buf, unsigned short buf_len)
{
	unsigned short real_out_len = 0, i = 0, data_len = 0;

	if (ring_buffer_p == NULL)
		return 0;
		
	data_len = GetRingBufferLen(ring_buffer_p);
	if (buf_len > data_len)
	{
		real_out_len = data_len;
	}
	else if (buf_len <= data_len)
	{
		real_out_len = buf_len;
	}

	for (i = 0; i < real_out_len; i++)
	{
		buf[i] = ring_buffer_p->buf[ring_buffer_p->out];
		ring_buffer_p->out = (ring_buffer_p->out + 1) % ring_buffer_p->size;
	}
	return i;
}
