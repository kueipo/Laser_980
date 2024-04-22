#ifndef __TASK_POLITYHIGH_H
#define __TASK_POLITYHIGH_H

#ifdef __cplusplus
 extern "C" {
#endif

enum TASK_LOCAL_INDEX{
	SENDLASERCOUNT,
	SENDTIME,
	TASK_LOCAL_TOTAL_QTY,
};

void Task_PolityHigh(void);
void Enable_PHTask(uint8_t index );

#ifdef __cplusplus
}
#endif
#endif
