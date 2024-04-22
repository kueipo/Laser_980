#ifndef __COMMON_TASK_H
#define __COMMON_TASK_H

#include "APP/APP_Common.h"

#include "Task/Task_FanFB.h"
#include "Task/Task_Console.h"
#include "Task/Task_FeedBack.h"
#include "Task/Task_FB_Protect.h"
#include "Task/Task_Protect.h"
#include "Task/Task_HeartbeatMessage.h"
#include "Task/Task_DeviceDetection.h"
#include "Task/Task_DeviceRun.h"

//#include "Task_Safeguard.h"
//#include "Task_Control.h"
//#include "Task_Mem.h"
//#include "Task_Sensor.h"
//#include "Task_Common.h"
//#include "Task_Idle.h"
//#include "Task_GPRS.h"
//#include "Task_COM.h"
//#include "Task_HCI.h"

//#define TASK0                         SG_Task
//#define TASK1                         Contrl_Task
//#define TASK2                         Mem_Task
//#define TASK3                         Sensor_Task
//#define TASK4                         GPRS_Task
//#define TASK5                         COM_Task
//#define TASK6                         HCI_Task
//#define TASK7                         Idle_Task
//
///////////////////ϵͳ������///////////////////
//#define SG                            0    
//#define SG_LOW_VOLT_DETECT            0
///////////////////����������///////////////////
//#define CONTROL                       1
//#define CONTROL_CHARGE_OPEN           0
//#define CONTROL_CHARGE_CLOSE          1
///////////////////�洢������///////////////////
//#define MEM                           2      
//#define MEM_WRITE_SOLID               0
//#define MEM_WRITE_SUBSOLID            1
//#define MEM_READ_SOLID                2
//#define MEM_READ_SUBSOLID             3

///////////////////������������///////////////////
//#define SENSOR                        3   
//#define SENSOR_NTC                    0
///////////////////GPRS������///////////////////
//#define GPRS                          4  
//#define GPRS_CMD_PROC                 0
//#define GPRS_STATE_PROC               1
//#define GPRS_DECODE                   2
///////////////////COM������///////////////////
//#define COM                           5  
//#define COM_STATE_PROC                0
///////////////////HCI������///////////////////
//#define HCI                           6 
//#define HCI_KEY                       0
//#define HCI_LED                       1
//#define HCI_BEEP                      2
///////////////////IDLE������///////////////////
//#define IDLE                          7
//#define IDLE_SUBTASK0                 0

//typedef struct
//{
//    uint8_t (*function)(uint8_t m_Event);//�������ĺ���ָ�� ����ִ��������
//}Task_Type;

//extern uint8_t g_Maintask;        //ϵͳ������
//extern uint8_t ga_Subtask[8];     //ϵͳ������


//extern Task_Type  Task_Struct[8];
//extern const uint8_t  ga_TaskMapTable[256];

//void Set_Task(uint8_t main_task,uint8_t sub_task);
//void Clr_Task(uint8_t main_task,uint8_t sub_task);
//uint8_t clear_task(uint8_t prio , uint8_t m_SYS_SubTask_prio);
void Task_TimeProc(uint8_t ucPeriod);

#endif
