
#ifndef	__TASK_FB_PROTECT_H
#define	__TASK_FB_PROTECT_H

/* App Index -----------------------------------------------------------------*/
enum TASK_FB_PROTECT_INDEX{
	TASK_FB_PROTECT_ERROR,
	TASK_FB_PROTECT_UPDATA,
	TASK_FB_PROTECT_VERSION,
	
};

/* Function prototypes -------------------------------------------------------*/
void Task_FB_Protect_Marks_Handler_Callback(void);
void Task_FB_Protect_Handler_Callback(void);
void Task_FB_Protect_Enable(uint8_t id, uint8_t delaystate);
void Task_FB_Protect_Search(void *buf);

#endif /* __TASK_FB_PROTECT_H */
