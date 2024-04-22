/**
 * @file UI_Level.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "UI_Level.h"
#include "display.h"

/*********************
 *      DEFINES
 *********************/
#define LEVEL_MAX	10
#define LEVEL_MIN	1

#define IMG_BG		 			IMG_LEVEL
#define IMG_BG_H				240
#define IMG_BG_V				240
#define IMG_BG_X_START			(LCD_WIDTH - IMG_BG_H) / 2	// 居中
#define IMG_BG_Y_START			(LCD_HEIGHT - IMG_BG_H) / 2 // 居中
#define IMG_BG_X_END			IMG_BG_X_START + IMG_BG_H
#define IMG_BG_Y_END			IMG_BG_Y_START + IMG_BG_H

#define IMG_ICO_UP				//"pic2"
#define IMG_ICO_UP_H			90
#define IMG_ICO_UP_V 			90
#define IMG_ICO_UP_X_START		(LCD_WIDTH - IMG_ICO_UP_H) / 2		// 居中
#define IMG_ICO_UP_Y_START		0									// 顶部
#define IMG_ICO_UP_X_END		IMG_ICO_UP_X_START + IMG_ICO_UP_H
#define IMG_ICO_UP_Y_END		IMG_ICO_UP_Y_START + IMG_ICO_UP_V

#define IMG_ICO_DOWN			//"pic3"
#define IMG_ICO_DOWN_H			90
#define IMG_ICO_DOWN_V 			90
#define IMG_ICO_DOWN_X_START	(LCD_WIDTH - IMG_ICO_DOWN_H) / 2	// 居中
#define IMG_ICO_DOWN_Y_START	(LCD_HEIGHT - IMG_ICO_DOWN_V) 		// 底部
#define IMG_ICO_DOWN_X_END		IMG_ICO_DOWN_X_START + IMG_ICO_DOWN_H
#define IMG_ICO_DOWN_Y_END		IMG_ICO_DOWN_Y_START + IMG_ICO_DOWN_V

/**********************
 *      TYPEDEFS
 **********************/
 
 /**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void UI_Level_BG_Init(void);
static void UI_Level_ICO_Up(void);
static void UI_Level_ICO_Down(void);
static void UI_Level_Val_Level(void);
static void UI_Level_BTN_Exe(void);
static void UI_Level_Buttom0Handle(void);
static void UI_Level_Buttom1Handle(void);
/**********************
 *  STATIC VARIABLES
 **********************/
static _Button_Coordinate btn[] = {
	/* key UP */
	{IMG_ICO_UP_X_START, IMG_ICO_UP_Y_START, IMG_ICO_UP_X_END, IMG_ICO_UP_Y_END},
	/* key DOWN */
	{IMG_ICO_DOWN_X_START, IMG_ICO_DOWN_Y_START, IMG_ICO_DOWN_X_END, IMG_ICO_DOWN_Y_END},
};

typedef union {
	struct
	{
		uint8_t bUpdataBG:1;
		uint8_t bUpdataIcoUp:1;
		uint8_t bUpdataIcoDown:1;
		uint8_t bUpdataLevel:1;
		uint8_t bUpdataBtn:1;
		uint8_t bBack:3;
	} FlagBit;
	uint8_t updataflag;
}Flag_Union;

typedef struct
{
	uint8_t ucBtnMumber;
	uint8_t ucBtnIndex;
	uint8_t ucLevel;
	_Button_Coordinate *btn;
	Flag_Union unFlag;
} UI_Level_Struct;

static UI_Level_Struct s_stLevelTcb = {
	.ucBtnMumber = sizeof(btn) / sizeof(btn[0]),
	.ucBtnIndex = 0xFF,
	.ucLevel = LEVEL_MIN,
	.btn = btn,
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * @brief  UI_Level_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void UI_Level_Init(void)
{
	s_stLevelTcb.unFlag.updataflag = 0XFF;
}

// --------------------------------------------------------------------------
/**
 * @brief  UI_Level_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void UI_Level_Task(void)
{
	if (s_stLevelTcb.unFlag.updataflag == false)
		return;

	UI_Level_BG_Init();
	UI_Level_BTN_Exe();
	UI_Level_ICO_Up();
	UI_Level_ICO_Down();
	UI_Level_Val_Level();

	/*  */
	s_stLevelTcb.unFlag.updataflag = false;
}

// -----------------------------------------------------------------------------
/**
 * @brief  UI_Level_ButtonHandle.
 * @note   None.
 * @param  Coordinate.
 * @retval None.
 */
bool UI_Level_ButtonHandle(int16_t *Coordinate)
{
	uint8_t index;
	for (index = 0; index < s_stLevelTcb.ucBtnMumber; index++)
	{
		if (Coordinate[0] > s_stLevelTcb.btn[index].start_x && Coordinate[0] < s_stLevelTcb.btn[index].end_x)
		{
			if (Coordinate[1] > s_stLevelTcb.btn[index].start_y && Coordinate[1] < s_stLevelTcb.btn[index].end_y)
			{
				break;
			}
		}
	}

	if (index >= s_stLevelTcb.ucBtnMumber)
	{
		return false;
	}

	s_stLevelTcb.ucBtnIndex = index;
	s_stLevelTcb.unFlag.FlagBit.bUpdataBtn = true;

	return true;
}

// --------------------------------------------------------------------------
/**
 * @brief  UI_Level_WriteLevel.
 * @note   None.
 * @param  level.
 * @retval None.
 */
void UI_Level_WriteLevel(uint8_t level)
{
	s_stLevelTcb.ucLevel = level;
	
	s_stLevelTcb.unFlag.FlagBit.bUpdataLevel = true;
}

/**
 * @brief  UI_Level_ReadLevel.
 * @note   None.
 * @param  None.
 * @retval ucLevel.
 */
uint8_t UI_Level_ReadLevel(void)
{
	return s_stLevelTcb.ucLevel;
}

// -----------------------------------------------------------------------------

/**********************
 *   STATIC FUNCTIONS
 **********************/
/**
 * @brief  UI_Level_BG_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Level_BG_Init(void)
{
	if (s_stLevelTcb.unFlag.FlagBit.bUpdataBG == false)
		return;

	char *img = IMG_BG;
	ImageDisplay(img, IMG_BG_X_START, IMG_BG_Y_START);
}

/**
 * @brief  UI_Level_ICO_Up.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Level_ICO_Up(void)
{
//	if (s_stLevelTcb.flag.bUpdataIcoUp == false)
//		return;

}

/**
 * @brief  UI_Level_ICO_Down.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Level_ICO_Down(void)
{
//	if (s_stLevelTcb.flag.bUpdataIcoDown == false)
//		return;

}

/**
 * @brief  UI_Level_ICO_Down.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Level_Val_Level(void)
{
	if (s_stLevelTcb.unFlag.FlagBit.bUpdataLevel == false)
		return;

	uint8_t number = s_stLevelTcb.ucLevel;
	uint8_t len;
	static uint8_t lastlen = 0xFF;
	uint8_t tmp;

	number %= 100;
	tmp = number;

	for (len = 1;; len++)
	{
		if (tmp < 10)
			break;
		tmp /= 10;
	}

	if (lastlen != len)	// Length changed
	{
		lastlen = len;
	//	UI_ClearWindow(((LCD_WIDTH / 2) - (Font20.Width * 2) / 2), 110, ((LCD_WIDTH / 2) + (Font20.Width * 2) / 2), 110 + Font20.Height, WHITE);
		UI_ClearWindow(106, 110, 134, 130, WHITE);
		
	//	UI_ClearWindow(((LCD_WIDTH / 2) - (Font20.Width * 2) / 2), 105, ((LCD_WIDTH / 2) - ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 105 + Font20.Height, WHITE);
	//	UI_ClearWindow(((LCD_WIDTH / 2) + ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 105, (120 + (Font20.Width * 2) / 2), 105 + Font20.Height, WHITE);
	}

//	UI_Paint_DrawNum(((LCD_WIDTH  - (Font20.Width * lastlen)) / 2), ((LCD_HEIGHT - Font20.Height) / 2), number, &Font20, WHITE, LIGHTGREEN);
	UI_Paint_DrawNum(((LCD_WIDTH  - (Font20.Width * lastlen)) >> 1), 110, number, &Font20, WHITE, LIGHTGREEN);
}

/**
 * @brief  UI_Level_BTN_Exe.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Level_BTN_Exe(void)
{
	if (s_stLevelTcb.unFlag.FlagBit.bUpdataBtn == false)
		return;
	
	switch (s_stLevelTcb.ucBtnIndex)
	{
	case 0:
	//	UI_Level_WriteLevel(++s_stLevelTcb.ucLevel);
		UI_Level_Buttom0Handle();
		break;
	case 1:
	//	UI_Level_WriteLevel(--s_stLevelTcb.ucLevel);
		UI_Level_Buttom1Handle();
		break;
	default:
		break;
	}
	s_stLevelTcb.ucBtnIndex = 0xFF;
}

static void UI_Level_Buttom0Handle(void)
{
	/* updata */
	uint16_t buff[1] = {0x00FF};
		
	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, HANDLE_POWER_SET, 1, buff);
}

static void UI_Level_Buttom1Handle(void)
{
	/* updata */
	uint16_t buff[1] = {0};
	
	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, HANDLE_POWER_SET, 1, buff);
}
