#ifndef		__TASK_H
#define		__TASK_H

#include	"DEV_Config.h"

#define	USING_LINK	0

//========================================================================
//                             �ⲿ�����ͱ�������
//========================================================================

/* APP��� */
enum TASK_INDEX{
	TASK_HEARTBEAT_MESSAGE = 0,
	TASK_SYSTEMDETECTION,
	TASK_CONSOLE,
	TASK_FB_PRO_HANDLER_CALLBACK,
	TASK_SYSTEMRUM,
#if USING_LINK
	TEST_POLITY_HIGH,
#endif
	TASK_TOTAL_QTY,
};

//========================================================================
//                               ���ر�������
//========================================================================
/* APP״̬�ṹ�� */
enum TASK_STATE{
	SUSPEND = 0,
	READY,
};

struct task
{
	/* APP״̬   0:����1:׼������ */
	enum TASK_STATE State;
	/* ����ʱ�� */
	unsigned char RunTime;
	/* �������� */
	unsigned char Period;
	/* �������� */
	void (*TaskHook)(void);
};

typedef struct task Task_Typedef;
// ========================================
// ========================================

extern Task_Typedef Task[];

void Task_Marks_Handler_Callback(void);
void Task_Pro_Handler_Callback(void);

int Link_Init(void);
#if USING_LINK
void InsertNode(uint8_t index);
void DelCurrentNode(void);
#endif
#endif
