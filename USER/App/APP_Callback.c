#include "APP_Common.h"

/*****************************************************************************
Function name : 
Description:    定时器中断回调函数
Author:
Input:
Return:
******************************************************************************/
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance == g_stTimCfg[TIM_CHNL_TIME_BASE].huart.Instance)
//	{
//		APP_TimeProc(1);
//	}
//}

/*****************************************************************************
Function name : 
Description:    key处理回调函数
Author:
Input:
Return:
******************************************************************************/
void HCI_KeyProcCallback(uint8_t trigger)
{
#if 0
	switch (trigger)
	{
	case SHOURT_PRO:
	{
		printf("short");
	}
	break;

	case LONG_PRO:
	{
		printf("long");
	}
	break;

	case DOUBLE_PRO:
	{
		printf("double");
	}
	break;

	case NO_PRO:
	default:
		break;
	}
#else
	UNUSED(trigger);
#endif
}
