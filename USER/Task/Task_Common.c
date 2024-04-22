
#include "Task/Task_Common.h"

//uint8_t g_Maintask;        //系统主任务
//uint8_t ga_Subtask[8];     //系统子任务

//#define TASK_ALL    0xff

//Task_Type  Task_Struct[8] = 
//{ //任务列表 TASK0优先级最高
//    TASK0,
//    TASK1,
//    TASK2,
//    TASK3,
//    TASK4,
//    TASK5,
//    TASK6,
//    TASK7
//};

//const uint8_t  ga_TaskMapTable[256] = 
//{
//    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
//    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
//};



//void Set_Task(uint8_t main_task,uint8_t sub_task)
//{
//  uint16_t mm,ss;
//  mm = 1<<main_task;
//  ss = 1<<sub_task;
//  g_Maintask |= mm;
//  ga_Subtask[main_task] |= ss;
//}

//void Clr_Task(uint8_t main_task,uint8_t sub_task)
//{
//    uint16_t ss;
//    if(sub_task == TASK_ALL)
//    {
//        ga_Subtask[main_task] = 0;
//    }
//    else
//    {        
//        ss = 1<<sub_task;
//        ga_Subtask[main_task] &= ~ss;
//    }
//}

//uint8_t clear_task(uint8_t prio , uint8_t m_SYS_SubTask_prio)
//{
//   ga_Subtask[prio] &=~ (1<<m_SYS_SubTask_prio);
//   if(ga_Subtask[prio] == 0)
//   {
//        g_Maintask &=~(1<<prio);
//        return true;
//   }
//   return false;
//}
