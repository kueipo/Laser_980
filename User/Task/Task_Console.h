
#ifndef __APP_DEVICEDETECTION_H
#define __APP_DEVICEDETECTION_H

#define FRAME_START_0					0XA5
#define FRAME_START_1					0X5A
#define	OFFSET_FRAME_LENGTH			0U
#define	OFFSET_DATA_TYPE				1U
#define OFFSET_DATA_TARGET_H		2U
#define OFFSET_DATA_TARGET_L		3U
#define	OFFSET_DATA_LENGTH			4U
#define OFFSET_DATA_CONTENT_START		5U

#define	MAX_BUFF_SIZE		128
typedef struct{
	unsigned char head;
	unsigned char tail;
	unsigned char buf[MAX_BUFF_SIZE];
}RINGBUFFER_ST;

void Task_Console(void);

#endif
