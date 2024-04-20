/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_DEVICEDETECTION_H
#define __TASK_DEVICEDETECTION_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
typedef struct {
	uint16_t FanSpeed[DEV_FAN_MAX_NUMBER];
} SystemData_TypeDef;

extern SystemData_TypeDef SystemData;

/* External functions --------------------------------------------------------*/
void Task_SysDete_Marks_Handler_Callback(void);
void Task_SystemDetection(void);

#endif /* __TASK_DEVICEDETECTION_H */
