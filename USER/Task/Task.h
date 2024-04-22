#ifndef		__TASK_H
#define		__TASK_H

#include	"DEV_Config.h"

#define	USING_LINK	0

//========================================================================
//                             外部函数和变量声明
//========================================================================

/* APP序号 */
enum TASK_INDEX{
	CTP_HANDLE = 0,
	REFRESH_POWER,
	REFRESH_TIME,
#if USING_LINK
	TEST_POLITY_HIGH,
#endif
	TASK_TOTAL_QTY,
};

//========================================================================
//                               本地变量声明
//========================================================================
/* APP状态结构体 */
//enum TASK_STATE{
//	SUSPEND = 0,
//	READY,
//};

struct task
{
	/* APP状态   0:挂起；1:准备就绪 */
	enum APP_STAT State;
	/* 运行时间 */
	unsigned char RunTime;
	/* 运用周期 */
	unsigned char Period;
	/* 操作函数 */
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

void Enable_Task(uint8_t index);
void Disable_Task(uint8_t index);
#endif
