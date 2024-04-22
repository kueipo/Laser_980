
#include "APP/APP_Common.h"
#include "button.h"
#include "touch.h"
#include "display.h"
#include "GUI_Paint.h"
#include "console.h"

#include "Task/Task.h"

#ifdef  USING_CRC16
#include "CRC16.h"
#endif
void (*operation_index)(void);

void CTP_Handle(void);
void Button_Handle(void);

void Last_Page(void);
void Next_Page(void);
void Clr_Data(void);
void UP_Data(void);
void DOWN_Data(void);
extern volatile uint8_t LaserJ;


volatile uint8_t BtnCnt = 0xFF;

/* ================================================================== */

/* MAIN */
BUTTON_ST MainButton_Tab[] = {
	[0].bFlag = false ,
	[0].X_Y = {.x1 = 65, .y1 = 65, .x2 = 175, .y2 = 175},
	
};

APP_STRUCT MAIN_APP_Tab[] = 
{
	APP_PageMain_Start,
};
/* ----------------------------------------------------------------- */

BUTTON_ST PowerButton_Tab[] = {
	[0].bFlag = true,
	[0].X_Y = {.x1 = 86, .y1 = 34,  .x2 = 150, .y2 = 86},
	
	[1].bFlag = true,
	[1].X_Y = {.x1 = 86, .y1 = 150, .x2 = 154, .y2 = 206},
	
};

APP_STRUCT POWER_APP_Tab[] = 
{
	DOWN_Data,
	UP_Data, 
};
		
BTN_STRUCT Btn = {
	.ui_idx = MAIN,
	
	/* MAIN */
	.page[0].btn = MainButton_Tab,
	.page[0].number = sizeof(MainButton_Tab)/sizeof(MainButton_Tab[0]),
	.page[0].app_idx = MAIN_APP_Tab,
	
	/* POWER */
	.page[1].btn = PowerButton_Tab,
	.page[1].number = sizeof(PowerButton_Tab)/sizeof(PowerButton_Tab[0]),
	.page[1].app_idx = POWER_APP_Tab,
	
	/* J */
	
};

void CTP_Handle(void)
{
//	static bool exe = 0;
//	static uint8_t btnidx = 0xFF;
//	static uint8_t lastbtnidx = 0xFF;
//	uint8_t idx = 0;
//	uint8_t t = 0;// i = 0;
//	static uint16_t laststa[2];
//	tp_dev.scan(0);
//	if (tp_dev.sta & TP_CATH_PRES) //之前是被按下的
//	{
//		tp_dev.sta &= ~(1 << 6); //标记按键松开

//		if (exe)
//			return;

//		for (t = 0; t < 1; t++) //只读取第一点
//		{
//			if ((tp_dev.sta) & (1 << t))
//			{
//				if (tp_dev.x[t] < 240 && tp_dev.y[t] < 240) // 判断是否越界
//				{
//					//	App[REFRESH_LASERCNT].State = SUSPEND;	//有按键禁止刷激光数量
//					//	App[REFRESH_TIME].State = SUSPEND;
//					
//				//	printf("x is:%d \r\n", tp_dev.x[t]);
//				//	printf("y is:%d \r\n", tp_dev.y[t]);
//					
//				//	App[REFRESH_TIME].RunTime = App[REFRESH_TIME].Period;			  //重装计

//					if (laststa[0] == 0xFFFF)
//					{
//						laststa[0] = tp_dev.x[t];
//						laststa[1] = tp_dev.y[t];
//					}
//					/* 滑动 */
//					if (laststa[0] > (tp_dev.x[t] + 80)) //向左滑
//					{
//					//	if (Button.ui_idx != MAIN)
//							Last_Page(); // 首页不支持滑动，只能按确认进入
//						exe = 1;
//					}
//					else if (tp_dev.x[t] > (laststa[0] + 80)) //向右滑
//					{
//					//	if (Button.ui_idx != PAGEPOWER)
//							Next_Page(); //不能返回到首页
//						exe = 1;
//					}
//					/* 点击 */
//					else
//					{
//						for (idx = 0; idx < Btn.page[Btn.ui_idx].number; idx++) // 匹配按键区域
//						{
//							if ((tp_dev.x[t] > Btn.page[Btn.ui_idx].btn[idx].X_Y.x1) && (tp_dev.y[t] > Btn.page[Btn.ui_idx].btn[idx].X_Y.y1) && (tp_dev.x[t] < Btn.page[Btn.ui_idx].btn[idx].X_Y.x2) && (tp_dev.y[t] < Btn.page[Btn.ui_idx].btn[idx].X_Y.y2))	
//							{
//								btnidx = idx;
//								if (btnidx == lastbtnidx) //长按
//								{

//									if ( Btn.page[Btn.ui_idx].btn[idx].bFlag )
//									{
//										if (BtnCnt == 0) // 开始计时
//										{
//											
//											Btn_log_d("button is ：%d \r\n", idx);
//											Btn_log_d("UI page is ：%d \r\n", Btn.ui_idx);
//										
//											operation_index = Btn.page[Btn.ui_idx].app_idx[btnidx].current_operation;			
//											if (operation_index != NULL)
//												(*operation_index)();
//											else
//												Btn_log_err("button is idx error");
//			
//											BtnCnt = 50;									 // 5*50=250ms
//										}
//									}
//								}
//								lastbtnidx = btnidx;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	else if (btnidx != 0xFF)
//	{
//		if (exe == 0)
//		{
//			/* 按键处理 */
//			operation_index = Btn.page[Btn.ui_idx].app_idx[btnidx].current_operation;
//			
//			if (operation_index != NULL)
//				(*operation_index)();
//			else
//				Btn_log_err("button is idx error");
//			
//			exe = 1;
//		}
//		btnidx = 0xFF;
//		lastbtnidx = btnidx;
//	}
//	else if ((tp_dev.sta & TP_PRES_DOWN) == 0) //松开
//	{
//		laststa[0] = 0xFFFF;
//		laststa[1] = 0xFFFF;
//		BtnCnt = 200;
//		exe = 0;
//	}
}

extern const struct fal_partition *pic0;
extern const struct fal_partition *pic1;
extern const struct fal_partition *pic2;
extern const struct fal_partition *pic3;

extern PAINT_TIME time;
extern volatile uint16_t LaserCNT;
void Button_Handle(void)
{
	Btn_log_d("handle\r\n");
}

void Next_Page(void)
{
	extern char* const picture1;
	extern char* const picture2;
	extern char* const picture3;
	extern char* const picture4;
	const char *p = NULL;
	
	
	switch (Btn.ui_idx)
	{
	case MAIN:
		p = picture4;
		break;
	case PAGEPOWER:
	case PAGETOTAL:
	default:
		return;
	}
	if ((Btn.ui_idx + 1) < PAGETOTAL)
		Btn.ui_idx++;
	
	extern void ImageDisplay_1(const char *partindex, uint16_t xStart, uint16_t yStart);
	ImageDisplay_1(p, 0, 0);
	
	Refresh_AllData();
}

void Last_Page(void)
{
	extern char* const picture0;
	extern char* const picture1;
	extern char* const picture2;
	const char *p = NULL;
	bool state;
	switch (Btn.ui_idx)
	{
		case PAGEPOWER:
			state = APP_IsSystemRun();
			if (state)
				p = picture1;
			else
				p = picture0;			
			break;
		case PAGETOTAL:
		case MAIN:
		default:
			return;
	}
	if (Btn.ui_idx)
		Btn.ui_idx--;
	
	extern void ImageDisplay_1(const char *partindex, uint16_t xStart, uint16_t yStart);
	ImageDisplay_1(p, 0, 0);
	
	Refresh_AllData();
}

void Clr_Data(void)
{
//	unsigned char temp[16] = {0};

	//	time.Hour = 0;
	//	time.Min = 0;
	//	time.Sec = 0;
	//	LaserCNT = 0;

//	temp[0] = 0x02;
//	temp[1] = 0x01;
//	Send_Data(temp, 2);

	//	App[REFRESH_TIME].State = READY;
	//	App[REFRESH_LASERCNT].State = READY;
	Btn_log_d("Clr data\r\n");
}

void UP_Data(void)
{
	uint16_t temp[1] = {0};
	uint16_t targe;
	
	switch (Btn.ui_idx)
	{
		case MAIN:
			break ;
		case PAGEPOWER:
			temp[0] = 0x01;
			targe = HANDLE_POWER_SET;
			break ;
		default :
			return ;
	}
	
	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, targe, 1, temp);
	
	Btn_log_d("up data\r\n");
}

void DOWN_Data(void)
{
	uint16_t temp[1] = {0};
	uint16_t targe;
	
	switch (Btn.ui_idx)
	{
		case MAIN:
			break ;
		case PAGEPOWER:
			temp[0] = 0x00;
			targe = HANDLE_POWER_SET;
			break ;
		default :
			return ;
	}
	
	APP_PackageData(DEV_INDEX_HANDLE_0, INDEX_TYPE_OPERATE, targe, 1, temp);
		
	Btn_log_d("down data\r\n");
}
