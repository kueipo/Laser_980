/**
 * @file UI.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "UI.h"
#include "FT5466/FT5466.h"
#include "main.h"
#include "UI_Paint.h"
#include "GUI_Paint.h"
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
typedef struct
{
	void (*InitTask)(void);
	void (*UiTask)(void);
	bool (*BtnHandle)(int16_t *p);
} UI_Page_TypeDef;
static UI_Page_TypeDef UI_Page_Tcb[] = {
	{*UI_Switch_Init, *UI_Switch_Task, *UI_Switch_ButtonHandle},
	{*UI_Level_Init, *UI_Level_Task, *UI_Level_ButtonHandle},
};

struct UI_Tcb
{
	uint8_t id;
	uint8_t id_max;
	UI_Page_TypeDef *page;
} UI_Tcb = {
	.id = 0,
	.id_max = sizeof(UI_Page_Tcb) / sizeof(UI_Page_Tcb[0]),
	.page = UI_Page_Tcb,
};

/**********************
 *      MACROS
 **********************/
#define WHITE				0xFFFF
#define LIGHTBLUE			0X7D7C	 

#include "display.h"
/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void UI_Init(void)
{
	UI_Tcb.page[UI_Tcb.id].InitTask();
}

void UI_Task(void)
{
	UI_Tcb.page[UI_Tcb.id].UiTask();
}

void UI_Switch_Next(void)
{
	if (++UI_Tcb.id >= UI_Tcb.id_max)
		UI_Tcb.id = 0;
}

void UI_Switch_Last(void)
{
	if (--UI_Tcb.id >= UI_Tcb.id_max)
		UI_Tcb.id = UI_Tcb.id_max - 1;
}

uint8_t UI_Read_PageID(void)
{
	return UI_Tcb.id;
}

enum BTN_STATE
{
	BTN_NULL = 0X00,
	BTN_PRESS,
	BTN_RELEASE,
	//	BTN_SHORT,
	//	BTN_LONG,
	//	BTN_GESTURE_LEFT,
	//	BTN_GESTURE_RIGHT,
};

#define BTN_PERIOD 10
#ifndef ABS_RETURN
#define ABS_RETURN(x, y) ((x) < (y)) ? ((y) - (x)) : ((x) - (y))
#endif

void UI_BTN_Handle(void)
{
	static int16_t Conrdinate[2] = {-1, -1};
	static int16_t GestureStart[2] = {-1, -1};
	static enum BTN_STATE BtnState = BTN_NULL;

	if (FT5466_Read_xy(Conrdinate, Conrdinate + 1) == true)
	{
		if (BtnState == BTN_NULL)
		{
			BtnState = BTN_PRESS;
			GestureStart[0] = Conrdinate[0];
			GestureStart[1] = Conrdinate[1];
		}
	}
	else
	{
		if (BtnState != BTN_NULL)
		{

			if (ABS_RETURN(GestureStart[0], Conrdinate[0]) > 80)
			{
				if (GestureStart[0] > Conrdinate[0]) // BTN_GESTURE_LEFT;
				{
					UI_Switch_Last();
				}
				else // BTN_GESTURE_RIGHT
				{
					UI_Switch_Next();
				}

				UI_Tcb.page[UI_Tcb.id].InitTask();
			}
			else
			{
				BtnState = BTN_RELEASE;
			}

			if (BtnState == BTN_RELEASE)
			{
				UI_Tcb.page[UI_Tcb.id].BtnHandle(Conrdinate);
			}

			BtnState = BTN_NULL;
		}
	}
}
/**********************
 *   STATIC FUNCTIONS
 **********************/