
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"
#include "Task/Task_FeedBack.h"

/* Variables -----------------------------------------------------------------*/
typedef struct 
{
	volatile bool bReady;
}PageMain_Struct;

__IOM PageMain_Struct s_stPageMain = {
	.bReady = false,
};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_PageMain_Start.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_PageMain_Start(void)
{
	uint16_t temp[1];
	temp[0] = 0x02;
	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, INDEX_SYSTEM_READY, 1, temp);
	
// 发送启动/停止指令
//	APP_LaserRunSotpSwitch();
//	temp[0] = (uint16_t)APP_IsSystemRun();
//	
//	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, INDEX_SYSTEM_READY, 1, temp);
//	
//	// 切换图标
//	extern char* const picture2;
//	extern char* const picture3;
//	const char *p = NULL;
//	
//	if (temp[0])
//		p = picture3;
//	else 
//		p = picture2;
//	
//	
//	extern void ImageDisplay_1(const char *partindex, uint16_t xStart, uint16_t yStart);
//	ImageDisplay_1(p, 67, 67);
}


/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

 /**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
 
 /**********************
 *  STATIC VARIABLES
 **********************/
 
 /**********************
 *      MACROS
 **********************/
 
 /**********************
 *   GLOBAL FUNCTIONS
 **********************/


/**********************
 *   STATIC FUNCTIONS
 **********************/

