
#include "Task/Task_Common.h"

#if USING_LINK
#include <stdio.h>
#include <stdlib.h>

//节点结构
typedef struct link {
	struct link * prior;
	uint8_t index;
	struct link * next;
}link;
//双链表的创建函数
link* InitLink(link * head);

static link * head=NULL;
#endif

#if USING_LINK
/* 放置高优先级 */
void Test_Polity_High(void)
{
	printf("Test High Polity !!!\r\n");
	DelCurrentNode();
}
#endif

//========================================================================
//========================================================================
Task_Typedef Task[]=
{	
	//State		RunTime	Period  current_operation	unit:10ms
	{ READY,	100,		100,		(*Task_Heartbeat_Message)	},
	{ READY,	10,			1,			(*Task_SystemDetection)	},
	{ READY,	20,			0,			(*Task_Console)	},
	{ READY,	30,			0,			(*Task_FB_Pro_Handler_Callback)	},
	{ READY,	40,			1,			(*Task_SystemRun)	},
	{ READY,	50,			50,			(*Task_Protect)	},
	{ READY,	60,			100,		(*APP_Fan_Task)	},
	{ READY,	70,			100,		(*APP_Protect_Task)	},
	{ READY,	80,			1,			(*Task_FB_Protect_Handler_Callback)	},
#if USING_LINK
	{ READY,	0,			0,			(*Test_Polity_High)	},
#endif
	/* Add new task here */
	{ READY,	0,			1,			(*Task_PolityHigh)	},
};

volatile uint8_t TaskQty = sizeof(Task) / sizeof(Task[0]);

//========================================================================
//========================================================================

//========================================================================
// 函数: Task_Handler_Callback
// 描述: 任务标记回调函数.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================
void Task_Marks_Handler_Callback(void)
{
	static unsigned char i;
	
	for (i=0;i<TaskQty;i++)
	{
		if(Task[i].RunTime)
			Task[i].RunTime--;
	}
}

struct task *nodelist;

//========================================================================
// 函数: Task_Pro_Handler_Callback
// 描述: 任务处理回调函数. 
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================
void Task_Pro_Handler_Callback(void)
{
#if USING_LINK
	uint8_t i = head->index;
	if (i >= TaskQty);
	else if( Task[i].RunTime == 0 && (Task[i].State == READY) )
	{
		Task[i].TaskHook();
	}
	head = head->next;
#else
	static uint8_t i = 0;
	
	Task_PolityHigh();
	
	if( Task[i].RunTime == 0 && (Task[i].State == READY) )
	{						
		Task[i].TaskHook();
		Task[i].RunTime = Task[i].Period;
	}
	i = (i + 1) % TaskQty;
#endif
}

#if USING_LINK
link *InitLink(link *head)
{
	link *P;

	//创建一个首元节点，链表的头指针为head
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
		{
			return;
		}
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
#endif

int Link_Init(void)
{
#if USING_LINK
	head = InitLink(head);
#else
	;
#endif
	return 0;
}
