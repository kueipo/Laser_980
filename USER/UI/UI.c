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
	bool Gesture;
} UI_Page_TypeDef;
static UI_Page_TypeDef UI_Page_Tcb[] = {
	{*UI_Switch_Init, *UI_Switch_Task, *UI_Switch_ButtonHandle, true},
	{*UI_Level_Init, *UI_Level_Task, *UI_Level_ButtonHandle, true},
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
	BTN_PRESSED,
	//  BTN_RELEASED,
	BTN_CLICKED,
	//	BTN_LONG_PRESSED,
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
	
	/* PRESSED */
	if (FT5466_Read_xy(Conrdinate, Conrdinate + 1) == true)
	{
		if (BtnState == BTN_NULL)
		{
			BtnState = BTN_PRESSED;
			GestureStart[0] = Conrdinate[0];
			GestureStart[1] = Conrdinate[1];
		}
		/* LONG_PRESSED */
		/* LONG_PRESSED_REPEAT */
	}
	/* RELEASE */
	else
	{
		if (BtnState != BTN_NULL)
		{
			/* GESTURE */
			if (ABS_RETURN(GestureStart[0], Conrdinate[0]) > 80)
			{
				if (UI_Tcb.page[UI_Tcb.id].Gesture)
				{
					/* BTN_GESTURE_LEFT */
					if (GestureStart[0] > Conrdinate[0])
					{
						UI_Switch_Last();
					}
					/* BTN_GESTURE_RIGHT */
					else
					{
						UI_Switch_Next();
					}

					UI_Tcb.page[UI_Tcb.id].InitTask();
				}
			}
			/* SHORT_CLICKED */
			/* CLICKED */
			else
			{
				BtnState = BTN_CLICKED;
			}
			
			
			if (BtnState == BTN_CLICKED)
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
