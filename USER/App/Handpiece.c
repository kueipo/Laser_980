#include "Handpiece.h"

//========================================================================
//                               本地常量声明	
//========================================================================

//========================================================================
//                               本地变量声明
//========================================================================
typedef struct {
	uint8_t spot;
	bool	redlight;
} Handpiece_TypeDef;
Handpiece_TypeDef Handpiece;
//========================================================================
//                               本地函数声明
//========================================================================

//========================================================================
//                            外部函数和变量声明
//========================================================================
/**
* @brief  初始化.
* @note   None.
* @param  None.
* @retval None.
*/
void Handpiece_Init(void)
{
	;
}

/**
* @brief  运行.
* @note   None.
* @param  None.
* @retval None.
*/
void Handpiece_Run(void)
{
	;
}

/**
* @brief  红描控制.
* @note   None.
* @param  state:FALSE off,TRUE on.
* @retval None.
*/
void Handpiece_RedLightControl(bool state)
{
	if (state == true )
	{
//		DEV_RED_LIGHT_ON;
	}
	else
	{
//		DEV_RED_LIGHT_OFF;
	}
}
