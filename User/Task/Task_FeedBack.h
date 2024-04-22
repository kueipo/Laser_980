/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef	__TASK_FEEDBACK_H
#define	__TASK_FEEDBACK_H

/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "Task.h"
	
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* App Index */
enum TASK_FB_INDEX{
	TASK_FB_SYSTEM_READY = 0X00,
	TASK_FB_OVERTEMP_PROTECT,
	TASK_FB_SET_TEMP_TH,
	TASK_FB_SET_WATERFLOW_PROTECT,
	TASK_FB_SET_HAND_PROTECT,
	TASK_FB_SET_SAFELOCKER_PROTECT,
	TASK_FB_SET_LASER_PULSE,
	TASK_FB_SET_LASER_PULSE_WIDTH,
	TASK_FB_SET_LASER_FREQUENCY,
	TASK_FB_SET_LASER_POWER,
	TASK_FB_SET_KEY_DELAY,
	TASK_FB_SET_LASER_MODE,
	TASK_FB_SET_LED,
	TASK_FB_SET_LASER_NUM,
	TASK_FB_SET_LASER_INDICATOR_POWER,
	TASK_FB_SET_WORK_TIME,
	TASK_FB_SET_LASER_COUNT,
	TASK_FB_GET_LASER_INFO,
	
	TASK_FB_UPDATA,
	TASK_FB_PRODUCT_DATE,
	TASK_FB_GET_VERSION,
	TASK_FB_SYSTEM_REBOOT,
	TASK_FB_TOTAL_QTY,
};
/* Exported macro ------------------------------------------------------------*/

/* External functions --------------------------------------------------------*/
void Task_FB_Marks_Handler_Callback(void);
void Task_FB_Pro_Handler_Callback(void);
void Enable_Feedback(uint8_t id, uint8_t delaystate);
void App_Matching(void *buf);

#endif /* __TASK_FEEDBACK_H */
