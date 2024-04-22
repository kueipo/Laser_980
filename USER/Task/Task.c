
#include "Task/Task_Common.h"

#if USING_LINK
	#include <stdio.h>
	#include <stdlib.h>

	// 节点结构
	typedef struct link
	{
		struct link *prior;
		uint8_t index;
		struct link *next;
	} link;
	// 双链表的创建函数
	link *InitLink(link *head);

	static link *head = NULL;

/* 放置高优先级 */
void Test_Polity_High(void)
{
	printf("Test High Polity !!!\r\n");
	DelCurrentNode();
}
#endif /* USING_LINK */

Task_Typedef Task[]=
{
/*	State		RunTime		Period   	current_operation	unit:5ms */
	{ READY,	200,		200,		(*Task_Heartbeat_Message)		},
//	{ READY,	0,			1,			(*Task_SystemDetection)		},
	{ READY,	0,			0,			(*Task_Console)	},
	{ READY,	0,			1,			(*Task_FB_Pro_Handler_Callback)	},
//	{ READY,	0,			1,			(*APP_DC24V_Task)	},
//	{ READY,	0,			2,			(*APP_Motor_Task)	},
	/* Add new task here */
	
#if USING_LINK
	{ READY,	0,			0,			(*Test_Polity_High)				},	/* task 5 Period： 0ms 	 */
#endif /* USING_LINK */
};
volatile unsigned char TaskQty = sizeof(Task) / sizeof(Task[0]);

/**
 * @brief  Task_Marks_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Marks_Handler_Callback(void)
{
	uint8_t i;

	for (i = 0; i < TaskQty; i++)
	{
		if (Task[i].RunTime)
			Task[i].RunTime--;
	}
}

/**
 * @brief  Task_Pro_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Pro_Handler_Callback(void)
{
#if USING_LINK
	uint8_t i = head->index;
	if (i >= TaskQty)
		;
	else if (Task[i].RunTime == 0 && (Task[i].State == READY))
	{
		Task[i].TaskHook();
	}
	head = head->next;
#else
	static uint8_t index = 0;

	if (Task[index].RunTime == 0 && (Task[index].State == READY))
	{
		Task[index].TaskHook();
		Task[index].RunTime = Task[index].Period;
	}
	index = (index + 1) % TaskQty;
#endif /* USING_LINK */
}

#if USING_LINK
link *InitLink(link *head)
{
	link *P;

	// 创建一个首元节点，链表的头指针为head
	head = (link *)malloc(sizeof(link));
	// 对节点进行初始化
	head->prior = head;
	head->next = head;
	head->index = 0;

	// 声明一个指向首元节点的指针，方便后期向链表中添加新创建的节点
	link *list = head;
	for (int i = 1; i < TaskQty; i++)
	{
		// 创建新的节点并初始化
		link *body = (link *)malloc(sizeof(link));
		body->prior = NULL;
		body->next = NULL;
		body->index = i;
		// 新节点与链表最后一个节点建立关系

		P = list->next;

		// next
		list->next = body;
		body->next = P;
		// prior
		body->prior = list;
		P->prior = body;

		// list永远指向链表中最后一个节点
		list = list->next;
	}

	// 返回新创建的链表
	return head;
}

void InsertNode(uint8_t index)
{
	link *list = head;
	link *P = list->next;

	link *temp = list;
	do
	{
		if (temp->index == index)
			return;
		temp = temp->next;
	} while (temp != list);

	// 创建新的节点并初始化
	link *body = (link *)malloc(sizeof(link));
	//  body->prior=NULL;
	//  body->next=NULL;
	body->index = index;
	// 新节点与链表前后一个节点建立关系
	//  next
	list->next = body;
	body->next = P;
	// prior
	body->prior = list;
	P->prior = body;
}

void DelCurrentNode(void)
{
	link *list = head;
	link *H = list->next;
	link *Q = list->prior;

	Q->next = H;
	H->prior = Q;

	free(list);
}
#endif /* USING_LINK */

int Link_Init(void)
{
#if USING_LINK
	head = InitLink(head);
#else
	;
#endif /* USING_LINK */
	return 0;
}

/**
 * @brief  Enable_PHTask.
 * @note   None.
 * @param  index.
 * @retval None.
 */
void Enable_Task(uint8_t index)
{
	if (index >= TaskQty)
		return;

	Task[index].State = READY;
}

/**
 * @brief  Disable_Task.
 * @note   None.
 * @param  index.
 * @retval None.
 */
void Disable_Task(uint8_t index)
{
	if (index >= TaskQty)
		return;

	Task[index].State = SUSPEND;
}
