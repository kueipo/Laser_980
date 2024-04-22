#include "button.h"
#include "touch.h"
#include "display.h"
#include "GUI_Paint.h"
#include "console.h"

#ifdef  USING_CRC16
#include "CRC16.h"
#endif
void (*operation_index)(void);

void CTP_Handle(void);
void Button_Handle(void);

void test_PIC_1(void);
void test_PIC_2(void);
void Last_Page(void);
void Next_Page(void);
void Clr_Data(void);
void UP_Data(void);
void DOWN_Data(void);
extern volatile uint8_t LaserJ;
extern volatile uint8_t LaserHZ;
extern volatile uint8_t LaserMS;

volatile uint8_t BtnCnt = 0xff;

#define APP_OPT_TABLE \
{ 										\
		Button_Handle, 		\
		CTP_Handle,				\
		Last_Page,				\
		Next_Page,				\
		Clr_Data,					\
		UP_Data,					\
		DOWN_Data,				\
}

typedef struct // 
{
	void (*current_operation)(void);
}APP_TABLE;
APP_TABLE AppTable[] = APP_OPT_TABLE;

/* �������� ������Ҫ��Ӱ��� */
#define MAIN_BUTTON_TABLE                                             \
{                                                                     \
		[BUTTON_0] = {.x1 =  49,		.y1 = 130, 		.x2 = 190,			.y2 = 230}, \
		[BUTTON_1] = {.x1 =  0,			.y1 = 0, 		.x2 = 0,			.y2 = 0}, 	\
		[BUTTON_2] = {.x1 =  0,			.y1 = 0, 		.x2 = 0,			.y2 = 0}, 	\
		[BUTTON_3] = {.x1 =  0,			.y1 = 0, 		.x2 = 0,			.y2 = 0}, 	\
}
#define OPERATION_BUTTON_TABLE_1                                      \
{                                                                     \
		[BUTTON_0] = {.x1 =  60,		.y1 = 160, 		.x2 = 180,			.y2 = 210}, \
		[BUTTON_1] = {.x1 =  0,			.y1 = 0, 	 	.x2 = 0,			.y2 = 0}, 	\
		[BUTTON_2] = {.x1 =  0,			.y1 = 0, 		.x2 = 0,			.y2 = 0}, 	\
		[BUTTON_3] = {.x1 =  0,			.y1 = 0, 		.x2 = 0,			.y2 = 0}, 	\
}

#define OPERATION_BUTTON_TABLE_2                                      \
{                                                                     \
		[BUTTON_0] = {.x1 =   0,		.y1 = 0, 		.x2 =  0,			.y2 = 0}, 	\
		[BUTTON_1] = {.x1 =   0,		.y1 = 0, 		.x2 = 0,			.y2 = 0}, 	\
		[BUTTON_2] = {.x1 =  100,		.y1 = 145, 		.x2 = 140,			.y2 = 185}, \
		[BUTTON_3] = {.x1 =  100,	  	.y1 =  45, 		.x2 = 140,			.y2 = 85}, 	\
}

#define OPERATION_BUTTON_TABLE_3                                      \
{                                                                     \
		[BUTTON_0] = {.x1 =   0,		.y1 = 	0, 	.x2 =  	0,		.y2 = 	0}, \
		[BUTTON_1] = {.x1 =   0,		.y1 =   0, 	.x2 =   0,		.y2 =   0}, \
		[BUTTON_2] = {.x1 = 100,		.y1 =  145, .x2 = 140,		.y2 = 185}, \
		[BUTTON_3] = {.x1 = 100,		.y1 =  45, 	.x2 = 140,		.y2 =	85}, \
}
/* APP���� ��� APP_OPT_TABLE �����дAPP���� */
#define APP_INDEX_TABLE        		 		\
{                               			\
		[MAIN] 				= { 3}, 						\
		[OPERATION_1] = { 4, 3}, 					\
		[OPERATION_2] = { 2, 3, 6, 5}, 		\
		[OPERATION_3] = { 2, 0, 6, 5}, 		\
}

BUTTON_STRUCT Button = { 
	.ui_idx = MAIN,
	.btn_idx = 0xff,
	.app_idx = APP_INDEX_TABLE,	
	/* ��ϰ������� ��ӳ�ʼ������ */
	.btn[MAIN] = MAIN_BUTTON_TABLE,
	.btn[OPERATION_1] = OPERATION_BUTTON_TABLE_1,
	.btn[OPERATION_2] = OPERATION_BUTTON_TABLE_2,
	.btn[OPERATION_3] = OPERATION_BUTTON_TABLE_3,
};

void CTP_Handle(void)
{
	static bool exe = 0;
	static uint8_t btnidx = 0xff;
	static uint8_t lastbtnidx = 0xff;
	uint8_t idx = 0;
	uint8_t t=0,i=0;
	static uint16_t laststa[2];
		tp_dev.scan(0);
		if(tp_dev.sta&TP_CATH_PRES)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<6);	//��ǰ����ɿ�
			
			if(exe) return;
						
			for(t=0;t<1;t++)	//ֻ��ȡ��һ��
			{
				if((tp_dev.sta)&(1<<t) )
				{
					if(tp_dev.x[t]<240&&tp_dev.y[t]<240)	// �ж��Ƿ�Խ��
					{
					//	App[REFRESH_LASERCNT].State = SUSPEND;	//�а�����ֹˢ��������
					//	App[REFRESH_TIME].State = SUSPEND;
						
						App[REFRESH_LASERCNT].RunTime = App[REFRESH_LASERCNT].Period /4;  //��װ��
						App[REFRESH_TIME].RunTime = App[REFRESH_TIME].Period;  //��װ��
												
						if(laststa[0] == 0xffff)
						{
							laststa[0] = tp_dev.x[t];
							laststa[1] = tp_dev.y[t];
						}
						
						if( laststa[0] > (tp_dev.x[t] +80))	//����
						{
							if(Button.ui_idx != MAIN)	Next_Page();	// ��ҳ��֧�ֻ�����ֻ�ܰ�ȷ�Ͻ���
							exe = 1;
						}
						else if( tp_dev.x[t] > (laststa[0] +80))	//���һ�
						{
							if(Button.ui_idx != OPERATION_1)	 Last_Page();		//���ܷ��ص���ҳ
							exe = 1;
						}
						else
						{
							for(idx = 0;idx < BUTTON_TOLAL ; idx++)	// ƥ�䰴������
							{
								if( (tp_dev.x[t] >= Button.btn[ Button.ui_idx ][idx].x1) && (tp_dev.y[t] >= Button.btn[ Button.ui_idx ][idx].y1) 				\
									&& (tp_dev.x[t] <= Button.btn[ Button.ui_idx ][idx].x2) && (tp_dev.y[t] <= Button.btn[ Button.ui_idx ][idx].y2) )
								{
									
									btnidx = idx;
									if(btnidx == lastbtnidx)	//����
									{
										if(btnidx == BUTTON_2 || btnidx == BUTTON_3 )
										{
											if(BtnCnt == 0)// ��ʼ��ʱ
											{
												Btn_log_d("button is ��%d \r\n",idx);
												Btn_log_d("UI page is ��%d \r\n",Button.ui_idx);
												i = Button.app_idx[ Button.ui_idx ][ idx ];	// ��ȡ������Ӧ��APP���
												operation_index = AppTable[i].current_operation;	// ��ȡAPP
												(*operation_index)();// ִ�е�ǰ��������
												BtnCnt = 50;	//5*50=250ms
											}
										}										
									}
									lastbtnidx = btnidx;
							//		Btn_log_d("button is ��%d \r\n",idx);
							//		Btn_log_d("UI page is ��%d \r\n",Button.ui_idx);
							//		i = Button.app_idx[ Button.ui_idx ][ idx ];	// ��ȡ������Ӧ��APP���
							//		operation_index = AppTable[i].current_operation;	// ��ȡAPP
							//		(*operation_index)();// ִ�е�ǰ��������
							//		exe = 1;
								}
							}
						}
					}
				}
			}
		}
		else if(btnidx != 0xff)
		{
			if(exe == 0)
			{
				Btn_log_d("button is ��%d \r\n",btnidx);
				Btn_log_d("UI page is ��%d \r\n",Button.ui_idx);
				i = Button.app_idx[ Button.ui_idx ][ btnidx ];	// ��ȡ������Ӧ��APP���
				operation_index = AppTable[i].current_operation;	// ��ȡAPP
				(*operation_index)();// ִ�е�ǰ��������				
				exe = 1;
			}
			btnidx = 0xff;
			lastbtnidx = btnidx;
		}
		else if( (tp_dev.sta&TP_PRES_DOWN) == 0 )	//�ɿ�
		{
			laststa[0]= 0xffff;
			laststa[1]= 0xffff;
			BtnCnt = 200;
			exe = 0;
		}
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
	const struct fal_partition *part;
	switch(Button.ui_idx)
	{
		case MAIN:
			part = pic1;
			break;
		case OPERATION_1:
			part = pic2;
			break;
		case OPERATION_2:
			part = pic3;
			break;
		case OPERATION_3:
		case PAGETOTAL:
		default:
			return;
	}
	Button.ui_idx++;
	ImageDisplay(part,0,0);
	Refresh_AllData();
}

void Last_Page(void)
{
	const struct fal_partition *part;
	switch(Button.ui_idx)
	{		
		case OPERATION_1:
			part = pic0;
			break;
		case OPERATION_2:
			part = pic1;
			break;
		case OPERATION_3:
			part = pic2;
			break;
		case PAGETOTAL:
		case MAIN:
		default:
			return;
	}
	Button.ui_idx--;
	ImageDisplay(part,0,0);
	Refresh_AllData();
}

void Clr_Data(void)
{
	unsigned char temp[16] = {0};
	
//	time.Hour = 0;
//	time.Min = 0;
//	time.Sec	= 0;
//	LaserCNT = 0;
	
	temp[0] = 0x02;
	temp[1] = 0x01;
	Send_Data(temp,2);
	
//	App[REFRESH_TIME].State = READY;
//	App[REFRESH_LASERCNT].State = READY;
	Btn_log_d("Clr data\r\n");	
}

void UP_Data(void)
{
	unsigned char temp[16] = {0};
	
	if(Button.ui_idx == OPERATION_2)
	{
//		LaserJ++;
		temp[0] = 0x03;
	}
	else if(Button.ui_idx == OPERATION_3)
	{			
//		LaserHZ++;
		temp[0] = 0x04;
	}
	temp[1] = 0x01;
	Send_Data(temp,2);
	
	App[REFRESH_J].State = READY;
	App[REFRESH_HZ].State = READY;
	Btn_log_d("up data\r\n");
}

void DOWN_Data(void)
{
	unsigned char temp[16] = {0};
	
	if(Button.ui_idx == OPERATION_2)
	{
//		LaserJ--;
		temp[0] = 0x03;
	}
	else if(Button.ui_idx == OPERATION_3)
	{
//		LaserHZ--;
		temp[0] = 0x04;
	}
	temp[1] = 0x02;
	Send_Data(temp,2);
	
	App[REFRESH_J].State = READY;
	App[REFRESH_HZ].State = READY;
	Btn_log_d("down data\r\n");
}

void Send_Data(unsigned char *data,unsigned char size)
{
	unsigned char i;
#ifdef  USING_CRC16
	unsigned int crc;
#endif
	unsigned char temp[16];
	
	temp[0] = 0XA5;
	temp[1] = 0X5A;
	temp[2] = size;
#ifdef  USING_CRC16
	temp[2] += 2;
#endif
	for(i=0;i<size;i++)
	{
		temp[3+i] = *(data+i);
	}
	
#ifdef  USING_CRC16
	crc = IOT_CRC16_XMODEM(data,size);
	temp[3+i] = crc>>8;
	temp[3+i+1] = crc&0xff;
	
	if ( HAL_UART_Transmit(DEV_UART_PORT , (uint8_t *)temp, size+5, 0xff) != HAL_OK )
	{
		/* Disable TXEIE and TCIE interrupts */
	//	CLEAR_BIT(DEV_UART_PORT->Instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

		DEV_UART_PORT->ErrorCode = HAL_UART_ERROR_NONE;
		
		/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
		SET_BIT(DEV_UART_PORT->Instance->CR3, USART_CR3_EIE);
		/* Enable the UART Parity Error interrupt and Data Register Not Empty interrupt */
		SET_BIT(DEV_UART_PORT->Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	}
#else
//	HAL_UART_Transmit(DEV_UART_PORT , (uint8_t *)temp, size+3, 0xFFFF);
	if ( HAL_UART_Transmit(DEV_UART_PORT , (uint8_t *)temp, size+3, 0xff) == HAL_TIMEOUT )
	{
		/* Disable TXEIE and TCIE interrupts */
		CLEAR_BIT(DEV_UART_PORT->Instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

		/* At end of Tx process, restore huart->gState to Ready */
		DEV_UART_PORT->gState = HAL_UART_STATE_READY;
	}
#endif
}
