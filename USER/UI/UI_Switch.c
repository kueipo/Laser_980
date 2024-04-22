/**
 * @file UI_Switch.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "UI_Switch.h"
#include "display.h"

/*********************
 *      DEFINES
 *********************/
#define IMG_BG_STOP 	IMG_PAUSE
#define IMG_BG_RUN		IMG_START
#define IMG_BG_H		240
#define IMG_BG_V		240
#define IMG_BG_X_START	(LCD_WIDTH - IMG_BG_H) / 2
#define IMG_BG_Y_START	(LCD_HEIGHT - IMG_BG_H) / 2
#define IMG_BG_X_END	IMG_BG_X_START + IMG_BG_H
#define IMG_BG_Y_END	IMG_BG_Y_START + IMG_BG_H

#define IMG_ICO_STATE_STOP		IMG_PAUSE_ICO
#define IMG_ICO_STATE_START		IMG_START_ICO
#define IMG_ICO_STATE_H			106
#define IMG_ICO_STATE_V 		106
#define IMG_ICO_STATE_X_START	(LCD_WIDTH - IMG_ICO_STATE_H) / 2
#define IMG_ICO_STATE_Y_START	(LCD_HEIGHT - IMG_ICO_STATE_V) / 2
#define IMG_ICO_STATE_X_END		IMG_ICO_STATE_X_START + IMG_ICO_STATE_H
#define IMG_ICO_STATE_Y_END		IMG_ICO_STATE_Y_START + IMG_ICO_STATE_V

/**********************
 *      TYPEDEFS
 **********************/
 
 /**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void UI_Switch_BTN_Exe(void);
static void UI_Switch_BG_Init(void);
static void UI_Switch_ICO_Start(void);
static void UI_Switch_Buttom0Handle(void);
/**********************
 *  STATIC VARIABLES
 **********************/
static _Button_Coordinate btn[] = {
	/* key 0 */
	{IMG_ICO_STATE_X_START, IMG_ICO_STATE_Y_START, IMG_ICO_STATE_X_END, IMG_ICO_STATE_Y_END},
};

typedef union {
	struct
	{
		uint8_t bUpdataBG:1;
		uint8_t bUpdataIcoStart:1;
		uint8_t bUpdataBtn:1;
		uint8_t bBack:5;
	} FlagBit;
	uint8_t updataflag;
}Flag_Union;

typedef struct
{
	uint8_t ucBtnMumber;
	uint8_t ucBtnIndex;
	_Button_Coordinate *btn;
	bool bOperation;
	Flag_Union unFlag;
} UI_Switch_Struct;

static UI_Switch_Struct s_stSwitchTcb = {
	.ucBtnMumber = sizeof(btn) / sizeof(btn[0]),
	.ucBtnIndex = 0xFF,
	.btn = btn,
	.bOperation = false,
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * @brief  UI_Switch_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void UI_Switch_Init(void)
{
	s_stSwitchTcb.unFlag.updataflag = 0xFF;
}

// --------------------------------------------------------------------------
/**
 * @brief  UI_Switch_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void UI_Switch_Task(void)
{
	if (s_stSwitchTcb.unFlag.updataflag == false)
		return;

	UI_Switch_BTN_Exe();

	UI_Switch_BG_Init();
	UI_Switch_ICO_Start();

	s_stSwitchTcb.unFlag.updataflag = false;
}

// --------------------------------------------------------------------------
/**
 * @brief  UI_Switch_WriteState.
 * @note   None.
 * @param  flag: true, flase.
 * @retval None.
 */
void UI_Switch_WriteState(bool flag)
{
	s_stSwitchTcb.bOperation = flag;
	
	s_stSwitchTcb.unFlag.FlagBit.bUpdataIcoStart = true;
}

// -----------------------------------------------------------------------------
/**
 * @brief  UI_Switch_ButtonHandle.
 * @note   None.
 * @param  Coordinate.
 * @retval None.
 */
bool UI_Switch_ButtonHandle(int16_t *Coordinate)
{
	uint8_t index;
	for (index = 0; index < s_stSwitchTcb.ucBtnMumber; index++)
	{
		if (Coordinate[0] > s_stSwitchTcb.btn[index].start_x && Coordinate[0] < s_stSwitchTcb.btn[index].end_x)
		{
			if (Coordinate[1] > s_stSwitchTcb.btn[index].start_y && Coordinate[1] < s_stSwitchTcb.btn[index].end_y)
			{
				break;
			}
		}
	}

	if (index >= s_stSwitchTcb.ucBtnMumber)
		return false;

	s_stSwitchTcb.ucBtnIndex = index;
	s_stSwitchTcb.unFlag.FlagBit.bUpdataBtn = true;

	return true;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
/**
 * @brief  UI_Switch_BTN_Exe.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Switch_BTN_Exe(void)
{
	if (s_stSwitchTcb.unFlag.FlagBit.bUpdataBtn == false)
		return;
	
	switch (s_stSwitchTcb.ucBtnIndex)
	{
	case 0:	// button 0 
		UI_Switch_Buttom0Handle();
		break;
	default:
		break;
	}

	s_stSwitchTcb.ucBtnIndex = 0xFF;
}

/**
 * @brief  UI_Switch_BG_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Switch_BG_Init(void)
{
	if (s_stSwitchTcb.unFlag.FlagBit.bUpdataBG == false)
		return;

	char *img;
	if (s_stSwitchTcb.bOperation)
	{
		img = IMG_BG_RUN;
	}
	else
	{
		img = IMG_BG_STOP;
	}
	ImageDisplay(img, IMG_BG_X_START, IMG_BG_Y_START);
}

/**
 * @brief  UI_Switch_ICO_Start.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Switch_ICO_Start(void)
{
	if (s_stSwitchTcb.unFlag.FlagBit.bUpdataIcoStart == false)
		return;

	char *img;
	if (s_stSwitchTcb.bOperation)
	{
		img = IMG_ICO_STATE_START;
	}
	else
	{
		img = IMG_ICO_STATE_STOP;
	}
	ImageDisplay(img, IMG_ICO_STATE_X_START, IMG_ICO_STATE_Y_START);
}

/**
 * @brief  UI_Switch_Buttom0Handle.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void UI_Switch_Buttom0Handle(void)
{
	/* updata */
	uint16_t buff[1] = {0};
	
	if (s_stSwitchTcb.bOperation == false)
		buff[0] = 0x00FF;
	
	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, INDEX_SYSTEM_READY, 1, buff);
}
