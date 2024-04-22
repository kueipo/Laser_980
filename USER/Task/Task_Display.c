
/* Includes ------------------------------------------------------------------*/
//#include "Task_DeviceRun.h"
//#include "DEV_Config.h"
#include "Task/Task_Common.h"
#include "LCD_2inch.h"
#include "fonts.h"
#include "GUI_Paint.h"
#include "button.h"
/* Define --------------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
void Heart_Beat(void);
void Refresh_AllData(void);
void Refresh_MS(void);
void Refresh_HZ(void);
void Refresh_J(void);
void Refresh_LaserCnt(void);
void Refresh_Time(void);

/* Variables -----------------------------------------------------------------*/
extern volatile uint32_t LaserCNT;
extern volatile uint8_t LaserJ;
extern volatile uint8_t LaserHZ;
extern volatile uint8_t LaserMS;
extern PAINT_TIME time;


typedef struct
{
	enum TASK_STATE State;
	void (*TaskHook)(void);
} LocalTask_TypeDef;

static LocalTask_TypeDef LocalTask[] = 
{
	{SUSPEND,	(*Refresh_AllData)},
	{READY,		(*Refresh_AllData)},
	{READY,		(*Refresh_MS)},
	{READY,		(*Refresh_HZ)},
	{READY,		(*Refresh_J)},
	{READY,		(*Refresh_LaserCnt)},
	{SUSPEND,	(*Refresh_Time)},		
};
static volatile uint8_t LocalTask_Total = sizeof(LocalTask) / sizeof(LocalTask[0]);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Task_Display_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Display_Init(void)
{
}

/**
 * @brief  Task_DisplayRun
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_DisplayRun(void)
{
	static uint8_t index = 0;

	LocalTask[index].TaskHook();
	index = (index + 1) % LocalTask_Total;
}

// ====================================================================
void Task_DisplayReady(enum DISPLAY_TASK_INDEX index)
{
	LocalTask[index].State = READY;
}

/**
 * @brief  Heart_Beat
 * @param  None
 * @retval None
 */
void Heart_Beat(void)
{
//	uint8_t temp[3] = {0};

//	//	App[HEART_BEAT].State = SUSPEND;

//	/* 上传版本号，按键状态 */
//	temp[0] = 0x10;
//	temp[1] = (uint8_t)VERSIONS;
//	//	if ( DEV_Digital_Read(KEY) == GPIO_PIN_RESET )	temp[1] = 0X00;
//	//	else temp[2] = 0X01;
//	temp[2] = 0X01;

//	//	Send_Data(temp, 3);
	;
}

void Refresh_AllData(void)
{
//	App[REFRESH_TIME].State = READY;
//	App[REFRESH_LASERCNT].State = READY;
//	App[REFRESH_J].State = READY;
//	App[REFRESH_HZ].State = READY;
	
	LocalTask[REFRESH_LASERCNT].State = READY;
	LocalTask[REFRESH_HZ].State = READY;
	LocalTask[REFRESH_J].State = READY;
	LocalTask[REFRESH_MS].State = READY;
}

void Refresh_MS(void)
{
	LocalTask[REFRESH_MS].State = SUSPEND;
}

void Refresh_HZ(void)
{
	static uint8_t lastlen = 0xFF;
	uint8_t hz;
	uint8_t len;
	uint8_t tmp;

	LocalTask[REFRESH_HZ].State = SUSPEND;

	if (Button.ui_idx == OPERATION_3)
	{
		hz = LaserHZ;
		hz %= 100;
		tmp = hz;

		for (len = 1;; len++)
		{
			if (tmp < 10)
				break;
			tmp /= 10;
		}

		if (lastlen != len)
		{
			lastlen = len;
		//	LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2) ,110,(120 + (Font20.Width *6)/2), 110+ Font20.Height, WHITE);

			LCD_2IN_ClearWindow((120 - (Font20.Width * 2) / 2), 105, (120 - ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 105 + Font20.Height, WHITE);
			LCD_2IN_ClearWindow((120 + ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 105, (120 + (Font20.Width * 2) / 2), 105 + Font20.Height, WHITE);
		}

		Paint_DrawNum((120 - (Font20.Width * lastlen) / 2), 105, hz, &Font20, WHITE, LIGHTGREEN);

	//	LCD_2IN_ClearWindow( (120 - (Font20.Width *2)/2) ,105,(120 + (Font20.Width *2)/2), 105+ Font20.Height, WHITE);
	//	Paint_DrawNum((120 -(Font20.Width *i)/2),105, hz, &Font20, WHITE, LIGHTGREEN);
	}
}

void Refresh_J(void)
{
	uint8_t len;
	static uint8_t lastlen = 0xff;
	uint8_t j;
	uint8_t tmp;

	LocalTask[REFRESH_J].State = SUSPEND;

	if (Button.ui_idx == OPERATION_2)
	{
		j = LaserJ;

		j %= 100;
		tmp = j;

		for (len = 1;; len++)
		{
			if (tmp < 10)
				break;
			tmp /= 10;
		}

		if (lastlen != len)
		{
			lastlen = len;
			//	LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2) ,110,(120 + (Font20.Width *6)/2), 110+ Font20.Height, WHITE);

			LCD_2IN_ClearWindow((120 - (Font20.Width * 2) / 2), 105, (120 - ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 105 + Font20.Height, WHITE);
			LCD_2IN_ClearWindow((120 + ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 105, (120 + (Font20.Width * 2) / 2), 105 + Font20.Height, WHITE);
		}

		Paint_DrawNum((120 - (Font20.Width * lastlen) / 2), 105, j, &Font20, WHITE, LIGHTGREEN);
	}
}


void Refresh_LaserCnt(void)
{
	uint8_t len;
	static uint8_t lastlen = 0xff;
	uint32_t cnt;
	uint32_t tmp;

	//	PAINT_TIME *pTime;

	LocalTask[REFRESH_LASERCNT].State = SUSPEND;

	if (Button.ui_idx == OPERATION_1)
	{
		cnt = LaserCNT;
		//	cnt %= 1000000;
		tmp = cnt;

		for (len = 1;; len++)
		{
			if (tmp < 10)
				break;
			tmp /= 10;
		}

		if (lastlen != len)
		{
			lastlen = len;
			//	LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2) ,110,(120 + (Font20.Width *6)/2), 110+ Font20.Height, WHITE);

			LCD_2IN_ClearWindow((120 - (Font20.Width * 6) / 2), 110, (120 - ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 110 + Font20.Height, WHITE);
			LCD_2IN_ClearWindow((120 + ((Font20.Width) * ((2 * lastlen) - 1)) / 2), 110, (120 + (Font20.Width * 6) / 2), 110 + Font20.Height, WHITE);
		}
		Paint_DrawNum((120 - (Font20.Width * lastlen) / 2), 110, cnt, &Font20, WHITE, LIGHTGREEN);

		//		pTime = &time;
		//		Paint_DrawTime((120 - (Font20.Width *(8))/2), 55, pTime, &Font20, WHITE, LIGHTGREEN );
	}
}


void Refresh_Time(void)
{
	PAINT_TIME *pTime;

	LocalTask[REFRESH_TIME].State = SUSPEND;

	if (Button.ui_idx == OPERATION_1)
	{
		pTime = &time;
		//	LCD_2IN_ClearWindow( (120 - (Font20.Width *(8-1))/2) ,55,(120 + (Font20.Width * (8-1))/2), 55+ Font20.Height, WHITE);
		Paint_DrawTime((120 - (Font20.Width * (8)) / 2), 55, pTime, &Font20, WHITE, LIGHTGREEN);
	}
}

