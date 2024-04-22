#ifndef __COMMON_TASK_H
#define __COMMON_TASK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "APP/APP_Common.h"
#include "Task/Task_FanFB.h"
#include "Task/Task_Console.h"
#include "Task/Task_Display.h"
#include "Task/Task_PolityHigh.h"
//#include "Task/Task_SendData.h"
#include "Task/Task_FeedBack.h"
#include "Task/Task.h"
#include "Task/Task_HeartbeatMessage.h"
#include "Task/Task_DeviceDetection.h"
	 
//#include "Task_Safeguard.h"
//#include "Task_Control.h"
//#include "Task_Mem.h"
//#include "Task_Sensor.h"
//#include "Task_Common.h"
//#include "Task_Idle.h"
//#include "Task_GPRS.h"
//#include "Task_COM.h"
//#include "Task_HCI.h"
//
//#define TASK0                         SG_Task
//#define TASK1                         Contrl_Task
//#define TASK2                         Mem_Task
//#define TASK3                         Sensor_Task
//#define TASK4                         GPRS_Task
//#define TASK5                         COM_Task
//#define TASK6                         HCI_Task
//#define TASK7                         Idle_Task
//
///////////////////系统主任务///////////////////
//#define SG                            0    
//#define SG_LOW_VOLT_DETECT            0
///////////////////控制主任务///////////////////
//#define CONTROL                       1
//#define CONTROL_CHARGE_OPEN           0
//#define CONTROL_CHARGE_CLOSE          1
///////////////////存储主任务///////////////////
//#define MEM                           2      
//#define MEM_WRITE_SOLID               0
//#define MEM_WRITE_SUBSOLID            1
//#define MEM_READ_SOLID                2
//#define MEM_READ_SUBSOLID             3

///////////////////传感器主任务///////////////////
//#define SENSOR                        3   
//#define SENSOR_NTC                    0
///////////////////GPRS主任务///////////////////
//#define GPRS                          4  
//#define GPRS_CMD_PROC                 0
//#define GPRS_STATE_PROC               1
//#define GPRS_DECODE                   2
///////////////////COM主任务///////////////////
//#define COM                           5  
//#define COM_STATE_PROC                0
///////////////////HCI主任务///////////////////
//#define HCI                           6 
//#define HCI_KEY                       0
//#define HCI_LED                       1
//#define HCI_BEEP                      2
///////////////////IDLE主任务///////////////////
//#define IDLE                          7
//#define IDLE_SUBTASK0                 0

//typedef struct
//{
//    uint8_t (*function)(uint8_t m_Event);//带参数的函数指针 用于执行任务函数
//}Task_Type;

//extern uint8_t g_Maintask;        //系统主任务
//extern uint8_t ga_Subtask[8];     //系统子任务


//extern Task_Type  Task_Struct[8];
//extern const uint8_t  ga_TaskMapTable[256];

//void Set_Task(uint8_t main_task,uint8_t sub_task);
//void Clr_Task(uint8_t main_task,uint8_t sub_task);
//uint8_t clear_task(uint8_t prio , uint8_t m_SYS_SubTask_prio);

#ifdef __cplusplus
}
#endif
#endif
