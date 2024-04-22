/******************** (C) COPYRIGHT 2015**************************************
* �ļ�����         : MSG2233.c
* ����             : 
* �汾             : V1.1
* ����             : 22/9/2015
* ����             : �ַ����������ʾ
********************************************************************************
* ע����� 
*
*
*******************************************************************************/

#include "FT6336.h"
#include "delay.h"
#include "ctiic.h"
//#include "IIC_TP.h"
//#include "sys_nvic.h"
//#include "funcdata.h"

#define X_LENGTH 240
#define Y_LENGTH 240

static TP_POINT tpPoint;
//tp��ȡ����״̬
unsigned char Tp_PressStaus = 0;
//����״̬�µ�ͨѶ��Ŀ
static unsigned int TpComOutCount;
static unsigned int TpComOutFlag;

void FT6336_Init(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOCʱ��

//	/*-------------------------------------------------------------*/
////	#define MSG_INT PBin(2)
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;// 
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
//	

//	EXTI_InitStructure.EXTI_Line=EXTI_Line14 ;	//ѡ���ж���·
//	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;  //����Ϊ�ж�����
//	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//EXTI_Trigger_Rising; //�����жϴ�����ʽΪ�½��ش���
//	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
//	EXTI_Init(&EXTI_InitStructure);	
//	

//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);	    //ѡ���жϹܽ�
//	
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02;
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

	
		/*-------------------------------------------------------------*/
//	#define MSG_RST PBout(7)
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;// 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��ͨ���ģʽ
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	
//	MSG_RST=1;
	MSG_RST(1);
//	delay_ms(1);
//	MSG_RST=0;
//	delay_ms(10);
//	MSG_RST=1;

	TpComOutCount = 0;
		
}

#define CTP_WRITE             				0x70
#define CTP_READ             					0x71
#define CTP_ACK_COUNTER        				10//150

#define TD_STAT_ADDR 0x2
#define TT_MODE_BUFFER_INVALID 0x08
#define TD_STAT_NUMBER_TOUCH 0x07

void CTP_I2C_delay()
{
	delay_us(1);
}

unsigned char CTP_I2C_READ(unsigned char reg, unsigned char *value, unsigned char len) 
{
	unsigned char i;
	CT_IIC_Start();  
	CTP_I2C_delay();
	CT_IIC_Send_Byte(CTP_WRITE);
	if(CT_IIC_Wait_Ack()!=0)			//�ȴ�Ӧ��
	{
		CT_IIC_Stop();
		return  0;						//Ӧ��ʧ��
	}
	CTP_I2C_delay();
	CT_IIC_Send_Byte(reg);
	if(CT_IIC_Wait_Ack()!=0)			//�ȴ�Ӧ��
	{
		CT_IIC_Stop();
		return  0;						//Ӧ��ʧ��
	}
	CTP_I2C_delay();
	CT_IIC_Stop();
	CTP_I2C_delay();
	CT_IIC_Start();
	CT_IIC_Send_Byte(CTP_READ);
	if(CT_IIC_Wait_Ack()!=0)			//�ȴ�Ӧ��
	{
		CT_IIC_Stop();
		return  0;						//Ӧ��ʧ��
	}
	CTP_I2C_delay();
	if (len <= 1)
    {
        *value =CT_IIC_Read_Byte(0);
		CTP_I2C_delay();
    }
	else
	{
	    for (i = 0; i< len - 1; i++)
	    {
	        *value++ =CT_IIC_Read_Byte(1);
			CTP_I2C_delay();
	    }
		*value =CT_IIC_Read_Byte(0);
		CTP_I2C_delay();
	}
    CT_IIC_Stop();
 	 
    return 1;
}

unsigned char CTP_I2C_Write(unsigned char reg, unsigned char value)
{
	CT_IIC_Start();  
	CTP_I2C_delay();
	CT_IIC_Send_Byte(CTP_WRITE);
	if(CT_IIC_Wait_Ack()!=0)			//�ȴ�Ӧ��
	{
		CT_IIC_Stop();
		return  0;						//Ӧ��ʧ��
	}
	CTP_I2C_delay();
	CT_IIC_Send_Byte(reg);
	if(CT_IIC_Wait_Ack()!=0)			//�ȴ�Ӧ��
	{
		CT_IIC_Stop();
		return  0;						//Ӧ��ʧ��
	}
	CTP_I2C_delay();
	CT_IIC_Send_Byte(value);
	if(CT_IIC_Wait_Ack()!=0)			//�ȴ�Ӧ��
	{
		CT_IIC_Stop();
		return  0;						//Ӧ��ʧ��
	}
	CTP_I2C_delay();
	CT_IIC_Stop();
	return 1;
}

void CTP_Init(void)
{
	unsigned char i;
	unsigned char lvalue;

	//����CTP zhouwei
//	CTP_I2C_Write(0x80, 0x1e); 
//	CTP_I2C_READ(0x80, &lvalue, 1);
	
	do{
		 CTP_I2C_READ(0xa3, &lvalue, 1);
		 i++;
		 delay_ms(50);
		 if((lvalue==0x06)||(lvalue==0x36)||(lvalue==0x64))
		 	break;
	  }
	while(i<20);
	if((lvalue==0x06)||(lvalue==0x36)||(lvalue==0x64))
	{

	}
	delay_ms(10);
//	CTP_I2C_Write(0x1B, 2);
}

#define TOUCH1_XH_ADDR 0x03
#define TOUCH2_XH_ADDR 0x09
#define TOUCH3_XH_ADDR 0x0F
#define TOUCH4_XH_ADDR 0x15
unsigned char values[4];
void CTP_GetTpOnePoint(const unsigned char x_base,TP_POINT *point,unsigned char *tpStu)
{
	
	CTP_I2C_READ(x_base, values, 4);
	if(x_base == 0x3)
	*tpStu = (values[0]>>6)&0x3;//(values[0]&0xC0);//
	point->x = (((unsigned int)(values[0]&0x0f))<<8) | values[1];
	point->y =   (((unsigned int)(values[2]&0x0f))<<8) | values[3];
}
unsigned char CTP_GetTpPoint(TP_POINT *Tmp_point,unsigned char *TpStu)
{
	unsigned char counter = 0,i;
	unsigned char lvalue;
	unsigned char PointsNum;
	TP_POINT tpPoint;
	int Tp_Point_x=0;
	int Tp_Point_y=0;
	const unsigned char x_base[] = {TOUCH1_XH_ADDR, TOUCH2_XH_ADDR, TOUCH3_XH_ADDR, TOUCH4_XH_ADDR};
	do{ //make sure data in buffer is valid
		CTP_I2C_READ(TD_STAT_ADDR, &lvalue, 1);
		if(counter++ == 0x30)
		{
		return 0;
		}
	}while(lvalue & TT_MODE_BUFFER_INVALID); 	

	CTP_I2C_READ(TD_STAT_ADDR, &lvalue, 1); 
	PointsNum = (unsigned char)(lvalue & TD_STAT_NUMBER_TOUCH);
	if((PointsNum == 0) || (PointsNum > 5))
		PointsNum = 1;
	for(i=0;i<PointsNum;i++)//
	{
		CTP_GetTpOnePoint(x_base[i], &tpPoint,TpStu);
		Tp_Point_x += tpPoint.x;
		Tp_Point_y += tpPoint.y;
	}
	Tmp_point->x = Tp_Point_x/PointsNum;
	Tmp_point->y = Tp_Point_y/PointsNum;
	return 1;
}

/***********************************************************************
* ��������    : TP_SpeedAdd
* ����        : ͨѶ��ʱ�����Լ�
* �����β�    :
* ����ֵ      :
************************************************************************/
void TP_ComCountAdd(void)
{
	if(TpComOutCount >0)
	{
		TpComOutCount--;	
		if(TpComOutCount == 0)
		{
			TpComOutFlag = 1;
			//��������
	//		Touch_Int();
		}
	}
}

/***********************************************************************
* ��������    : ReadTpComOutFlag
* ����        : ͨѶ��ʱ��ʶ
* �����β�    : ��
* ����ֵ      : ��
************************************************************************/
unsigned int ReadTpComOutFlag(void)
{
	return TpComOutFlag;
}
/***********************************************************************
* ��������    : ClearTpComOutFlag
* ����        : ���ͨѶ��ʱ��ʶ
* �����β�    : ��
* ����ֵ      : ��
************************************************************************/
void ClearTpComOutFlag(void)
{
	TpComOutFlag = 0;
}
unsigned char TpStuV = 0;
//��ȡ����
unsigned char  ReadTpPoint(void)
{
	int Tp_Point_x=0;
	int Tp_Point_y=0;

	TP_POINT tptmpPoint;	
	TpStuV = 0;
	if(CTP_GetTpPoint(&tptmpPoint,&TpStuV))
	{
			if(TpStuV == 1)
			{
				//�˴�������ָ�ɿ�
				if(Tp_PressStaus ==TP_Stu_Press)
				{
				Tp_PressStaus = TP_Stu_DoPress;
				}
				TpComOutCount = 0;
				return 1;
			}
			Tp_Point_x=tptmpPoint.x;//�õ�X
			Tp_Point_y=tptmpPoint.y;//�õ�y				
			
			if(Tp_PressStaus == TP_Stu_NoPress)
			{
				//����ɴ�����
				tpPoint.x=Tp_Point_y;
				tpPoint.y=Tp_Point_x;
			}
			
			Tp_PressStaus = TP_Stu_Press;

			return 1;
	}
	else
	{
			//У��ʧ��
			Tp_Point_x=-1;
			Tp_Point_y=-1;
			return 0;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin ==GPIO_PIN_8)
	{
		TpComOutCount = 35;
	//	ReadTpPoint();
	}
}
//void  EXTI4_15_IRQHandler(void)
//{
//	#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//		OSIntEnter();	 
//	#endif
////	if(EXTI_GetITStatus(EXTI_Line14)!=RESET)
////	{
////		TpComOutCount = 35;
////		//��������
////		Touch_Int();
////		EXTI_ClearITPendingBit(EXTI_Line4);
////	}
////	
////	if(__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)
////  { 
////    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
////    HAL_GPIO_EXTI_Callback(GPIO_Pin);
////  }
//	
//	#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//		OSIntExit();											 
//	#endif
//}


/***********************************************************************
* ��������    : ReadTpPressStu
* ����        : ��ȡTp״̬
* �����β�    : ��
* ����ֵ      : ��
************************************************************************/
unsigned char ReadTpPressStu(void)
{
	return Tp_PressStaus;
}
/***********************************************************************
* ��������    : SetTpPressStu
* ����        : ���ð���״̬
* �����β�    : ��
* ����ֵ      : ��
************************************************************************/
void ClearTpPressStu(void)
{
	Tp_PressStaus = TP_Stu_NoPress ;
}
/***********************************************************************
* ��������    : getTPPoint
* ����        : ��ȡ����
* �����β�    : ��
* ����ֵ      : ��
************************************************************************/
void getTPPoint(TP_POINT *point)
{

		point->x = tpPoint.x;
		point->y = tpPoint.y;

//	point->x = tpPoint.x;
//	point->y = tpPoint.y;
}

