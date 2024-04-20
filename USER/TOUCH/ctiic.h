#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "DEV_Config.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//���ݴ�����-IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//********************************************************************************
//��
////////////////////////////////////////////////////////////////////////////////// 	

//IO��������
#define CT_SDA_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PI3����ģʽ
#define CT_SDA_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} 	//PI3���ģʽ
//IO��������	 
//#define CT_IIC_SCL  PHout(6)  //SCL
//#define CT_IIC_SDA  PIout(3)  //SDA	 
//#define CT_READ_SDA PIin(3)   //����SDA 
 
#define CT_IIC_SCL(_value)	 	HAL_GPIO_WritePin(CPT_IIC_SCK, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define CT_IIC_SDA(_value) 		HAL_GPIO_WritePin(CPT_IIC_SDA, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define CT_READ_SDA 					HAL_GPIO_ReadPin(CPT_IIC_SDA)


//IIC���в�������
void CT_IIC_Init(void);                							//��ʼ��IIC��IO��				 
void CT_IIC_Start(void);														//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  													//����IICֹͣ�ź�
void CT_IIC_Send_Byte(unsigned char txd);						//IIC����һ���ֽ�
unsigned char CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
unsigned char CT_IIC_Wait_Ack(void); 								//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);															//IIC����ACK�ź�
void CT_IIC_NAck(void);															//IIC������ACK�ź�

#endif


//#ifndef __MYCT_IIC_H
//#define __MYCT_IIC_H
//#include "sys.h"
//#include "gpio.h"
////////////////////////////////////////////////////////////////////////////////////	 
////������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
////ALIENTEK STM32������
////���ݴ�����-IIC ��������	   
////����ԭ��@ALIENTEK
////������̳:www.openedv.com
////��������:2015/12/30
////�汾��V1.0
////��Ȩ���У�����ؾ���
////Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
////All rights reserved									  
////********************************************************************************
////��
//////////////////////////////////////////////////////////////////////////////////// 	

////IO��������
//#define CT_SDA_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PI3����ģʽ
//#define CT_SDA_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} 	//PI3���ģʽ
////IO��������	 
//#define CT_IIC_SCL  PBout(6)  //SCL
//#define CT_IIC_SDA  PBout(7)  //SDA	 
//#define CT_READ_SDA PBin(7)   //����SDA 
// 

////IIC���в�������
//void CT_IIC_Init(void);                	//��ʼ��IIC��IO��				 
//void CT_IIC_Start(void);				//����IIC��ʼ�ź�
//void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
//void CT_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
//u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
//u8 CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
//void CT_IIC_Ack(void);					//IIC����ACK�ź�
//void CT_IIC_NAck(void);					//IIC������ACK�ź�

//#endif





