#include "console.h"
#include "usart.h"
#include "DEV_Config.h"
#include "LCD_2inch.h"
#include "button.h"
#include "ymodem.h"
#include <fal.h>

#ifdef USING_CRC16
	#include "CRC16.h"
#endif

RINGBUFFER_ST RecBuff;

volatile uint32_t LaserCNT = 0;
volatile uint8_t LaserJ = 0;
volatile uint8_t LaserHZ = 0;
volatile uint8_t LaserMS = 0;

#define	DATA_LENTGH_LOCATION	0
#define	DATA_TYPE_LOCATION		1
#define	DATA_CONTENT_START		2
#define	COMMAND_LCD						0X01
#define	COMMAND_OPT						0X02
#define	COMMAND_MS						0X03
#define	COMMAND_HZ						0X04
#define	COMMAND_J							0X05
#define	COMMAND_REBOOT				0X06
#define	COMMAND_RS_VER				0X08
#define	UPDATA_APP						0X10
#define	UPDATA_PIC						0X11
#define	DIS_TIME							0X20
#define DIS_LASER_CNT					0X21
#define DIS_J									0X22
#define	DIS_HZ								0X23

PAINT_TIME time;

LED_DEVICE Led;

void Console_Init(void)
{
	uint8_t i;
	RecBuff.head = 0;
	RecBuff.tail = 0;
	
	for (i=0; i<MAX_BUFF_SIZE; i++)	RecBuff.buf[i] = 0;
	
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	SET_BIT(DEV_UART_PORT->Instance->CR3, USART_CR3_EIE);
	/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
	SET_BIT(DEV_UART_PORT->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
}

extern const struct fal_partition *opt_area;
extern const struct fal_partition *pic0;
extern const struct fal_partition *pic1;
extern const struct fal_partition *pic2;
extern const struct fal_partition *pic3;
extern const struct fal_partition *download;
#ifdef UPDATA_FACTORY_FIRMWARE
extern const struct fal_partition *factory;
#endif
extern const struct fal_partition	*env;

COM_StatusTypeDef SerialDownload(void);
void cpu_reset(void);

void Console_Handle(void)
{
	uint8_t ch;
	uint32_t temp;
	
	uint32_t Tickstart;
	uint32_t Timeout = 1000;
	
	static uint8_t step = 0;
	static uint8_t Prot_buf[16]	= {0};
	static uint8_t idx = 0;
	
	Tickstart = HAL_GetTick();
	while (RecBuff.head != RecBuff.tail)
	{

		if ((HAL_GetTick() - Tickstart) > Timeout) 	break;	//防止长时间停止
		
		ch = RecBuff.buf[RecBuff.tail];
		RecBuff.tail = ( (RecBuff.tail+1)%MAX_BUFF_SIZE );	//防止越界非法访问
	//	HAL_UART_Transmit(DEV_UART_PORT , (uint8_t *)&ch, 1, 0x00FF);
		
		switch (step)
		{
			case 0:
				if(0xA5 == ch)	step++;
				break;
			case 1:
				if (0x5A == ch)	step++;
				else step = 0;
				break;
			case 2:
				if (ch <= 0)	step = 0;
				else
				{
					Prot_buf[idx++] = ch;
					step++;
				}
				break;
			case 3:
				if (idx == Prot_buf[DATA_LENTGH_LOCATION])	//接收最后一位
				{
					Prot_buf[idx] = ch;
			//		HAL_UART_Transmit(DEV_UART_PORT , (uint8_t *)Prot_buf, Prot_buf[0]+1, 0x0fFF);
					
					step = 0;
					idx = 0;
				#ifdef USING_CRC16
					temp = Prot_buf[ Prot_buf[DATA_LENTGH_LOCATION] -1 ] << 8;
					temp += Prot_buf[ Prot_buf[DATA_LENTGH_LOCATION] ] ;
					if (IOT_CRC16_XMODEM( (Prot_buf+DATA_LENTGH_LOCATION+1), Prot_buf[DATA_LENTGH_LOCATION] -2 ) != temp )
					{break;}
				#endif
			//===============================================================================				
					switch( Prot_buf[DATA_TYPE_LOCATION])
					{
						case COMMAND_LCD:
							if( Prot_buf[DATA_CONTENT_START] <=4 )
							{
								LCD_2IN_SetBackLight(250* Prot_buf[DATA_CONTENT_START]);
							}					
							break;
						case COMMAND_OPT:
							break;
						case COMMAND_MS:
							LaserMS = Prot_buf[DATA_CONTENT_START]%100;
							App[REFRESH_MS].State = READY;
							break;
						case COMMAND_HZ:
							LaserHZ = Prot_buf[DATA_CONTENT_START]%100;
							App[REFRESH_HZ].State = READY;
							break;
						case COMMAND_J:
							LaserJ = Prot_buf[DATA_CONTENT_START]%100;
							App[REFRESH_J].State = READY;
							break;
						case COMMAND_REBOOT:
							cpu_reset();	//重启
							break;
						case COMMAND_RS_VER:
							Prot_buf[0] = 0X10;
							Prot_buf[1] = (uint8_t)VERSIONS;
							Send_Data(Prot_buf, 2);
							break;
					/* 升级APP */
						case UPDATA_APP:
							switch(Prot_buf[DATA_CONTENT_START])
							{
								case 0:
									opt_area = download;
									if( SerialDownload() == COM_OK)	//下载完成
									{						
										fal_partition_erase_all(env);	//擦除
										ch = 0x5A;
										if(fal_partition_write(env, 0, (uint8_t*) &ch, 1) >= 0 ) cpu_reset();	//重启
									}									
									break;
								case 1:
								#ifdef UPDATA_FACTORY_FIRMWARE
									opt_area = factory;
									if ( SerialDownload() == COM_OK )
									{
								#endif
										fal_partition_erase_all(env);	//擦除
										ch = 0xA5;
										if ( fal_partition_write(env, 0, (uint8_t*) &ch, 1) >= 0 ) cpu_reset();	//重启
								#ifdef UPDATA_FACTORY_FIRMWARE
									}
								#endif
									break;
								default:
									break;
							}
							break;
						case UPDATA_PIC:
							switch(Prot_buf[DATA_CONTENT_START])
							{
								case 0:
									opt_area = pic0;								
									break;
								case 1:
									opt_area = pic1;
									break;
								case 2:
									opt_area = pic2;
									break;
								case 3:
									opt_area = pic3;
									break;
								default:
									return;
							}
							SerialDownload();
							cpu_reset();	//重启
							break;
						case DIS_TIME:
							time.Hour = Prot_buf[DATA_CONTENT_START]%24;
							time.Min = Prot_buf[DATA_CONTENT_START+1]%60;
							time.Sec = Prot_buf[DATA_CONTENT_START+2]%60;
							App[REFRESH_TIME].State = READY;
							break;
						case DIS_LASER_CNT:
							temp = Prot_buf[DATA_CONTENT_START];
							temp = temp<<8;
							temp += Prot_buf[DATA_CONTENT_START+1];
							temp = temp<<8;
							temp += Prot_buf[DATA_CONTENT_START+2];
							temp = temp<<8;
							temp += Prot_buf[DATA_CONTENT_START+3];
							LaserCNT = temp%1000000;
							App[REFRESH_LASERCNT].State = READY;
							Led.cnt = 200;
							if (Led.stat == 0)
							{
								Led.stat = 1;
								LED_ON;
							}
							break;
					}
			//===============================================================================
			//		for(idx=0;idx<16;idx++)	Prot_buf[idx] = 0;
			//		idx = 0;
					return;
				}
				else
				{
					Prot_buf[idx++] = ch;
				}
		}
	}
}

void Refresh_Time(void)
{
	PAINT_TIME *pTime;
	
	App[REFRESH_TIME].State = SUSPEND;
	
	if(Button.ui_idx == OPERATION_1)
	{
		pTime = &time;
	//	LCD_2IN_ClearWindow( (120 - (Font20.Width *(8-1))/2) ,55,(120 + (Font20.Width * (8-1))/2), 55+ Font20.Height, WHITE);
		Paint_DrawTime((120 - (Font20.Width *(8))/2), 55, pTime, &Font20, WHITE, LIGHTGREEN );
	}
}
	
void Refresh_LaserCnt(void)
{
	uint8_t len;
	static uint8_t lastlen = 0xff;
	uint32_t cnt;
	uint32_t tmp;
	
	PAINT_TIME *pTime;
	
	App[REFRESH_LASERCNT].State = SUSPEND;
	
	if(Button.ui_idx == OPERATION_1)
	{
		cnt = LaserCNT;		
	//	cnt %= 1000000;
		tmp = cnt;
		
		for(len=1;;len++)
		{			
			if (tmp < 10)	break;
			tmp /= 10;
		}
		
		if (lastlen != len)
		{
			lastlen = len;
		//	LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2) ,110,(120 + (Font20.Width *6)/2), 110+ Font20.Height, WHITE);
						
			LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2),					110,(120 - ((Font20.Width)*((2*lastlen) - 1))/2), 	110+ Font20.Height, WHITE);
			LCD_2IN_ClearWindow( (120 + ((Font20.Width)*((2*lastlen) - 1))/2),	110,(120 + (Font20.Width *6)/2), 					110+ Font20.Height, WHITE);
			
		}
		Paint_DrawNum( (120 -(Font20.Width *lastlen)/2),110, cnt, &Font20, WHITE, LIGHTGREEN);	
		
//		pTime = &time;
//		Paint_DrawTime((120 - (Font20.Width *(8))/2), 55, pTime, &Font20, WHITE, LIGHTGREEN );
	}
}

void Refresh_J(void)
{
	uint8_t len;
	static uint8_t lastlen = 0xff;
	uint8_t j;
	uint8_t tmp;
	
	App[REFRESH_J].State = SUSPEND;
	
	
	
	if(Button.ui_idx == OPERATION_2)
	{
		j = LaserJ;
		
		j %= 100;
		tmp = j;
		
		for(len=1;;len++)
		{
			if (tmp < 10)	break;
			tmp /= 10;			
		}
		
		if (lastlen != len)
		{
			lastlen = len;
		//	LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2) ,110,(120 + (Font20.Width *6)/2), 110+ Font20.Height, WHITE);
						
			LCD_2IN_ClearWindow( (120 - (Font20.Width *2)/2),					105,(120 - ((Font20.Width)*((2*lastlen) - 1))/2), 	105+ Font20.Height, WHITE);
			LCD_2IN_ClearWindow( (120 + ((Font20.Width)*((2*lastlen) - 1))/2),	105,(120 + (Font20.Width *2)/2), 					105+ Font20.Height, WHITE);
			
		}
				
		Paint_DrawNum((120 -(Font20.Width *lastlen)/2 ),105, j, &Font20, WHITE, LIGHTGREEN);
	}		
}

void Refresh_HZ(void)
{
	uint8_t hz;
	uint8_t len;
	static uint8_t lastlen = 0xff;	
	uint8_t tmp;
	
	App[REFRESH_HZ].State = SUSPEND;
	
	if(Button.ui_idx == OPERATION_3)
	{		
		hz = LaserHZ;
		hz %= 100;
		tmp = hz;
		
		for(len=1;;len++)
		{
			if (tmp < 10)	break;
			tmp /= 10;			
		}
		
		if (lastlen != len)
		{
			lastlen = len;
		//	LCD_2IN_ClearWindow( (120 - (Font20.Width *6)/2) ,110,(120 + (Font20.Width *6)/2), 110+ Font20.Height, WHITE);
						
			LCD_2IN_ClearWindow( (120 - (Font20.Width *2)/2),					105,(120 - ((Font20.Width)*((2*lastlen) - 1))/2), 	105+ Font20.Height, WHITE);
			LCD_2IN_ClearWindow( (120 + ((Font20.Width)*((2*lastlen) - 1))/2),	105,(120 + (Font20.Width *2)/2), 					105+ Font20.Height, WHITE);	
		}
				
		Paint_DrawNum((120 -(Font20.Width *lastlen)/2 ),105, hz, &Font20, WHITE, LIGHTGREEN);
			
//		LCD_2IN_ClearWindow( (120 - (Font20.Width *2)/2) ,105,(120 + (Font20.Width *2)/2), 105+ Font20.Height, WHITE);
//		Paint_DrawNum((120 -(Font20.Width *i)/2),105, hz, &Font20, WHITE, LIGHTGREEN);	
	}
}

void Refresh_MS(void)
{
	App[REFRESH_MS].State = SUSPEND;
}

void Refresh_AllData(void)
{
	App[REFRESH_TIME].State = READY;
	App[REFRESH_LASERCNT].State = READY;
	App[REFRESH_J].State = READY;
	App[REFRESH_HZ].State = READY;
}

/**
  * @brief  Heart_Beat
  * @param  None
  * @retval None
  */
void Heart_Beat(void)
{
	uint8_t temp[3] = {0};
	
	//	App[HEART_BEAT].State = SUSPEND;
	
	/* 上传版本号，按键状态 */
	temp[0] = 0x10;
	temp[1] = (uint8_t)VERSIONS;
//	if ( DEV_Digital_Read(KEY) == GPIO_PIN_RESET )	temp[1] = 0X00;
//	else temp[2] = 0X01;
	temp[2] = 0X01;
	
	Send_Data(temp, 3);
}
