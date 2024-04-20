#ifndef __FT5206_H
#define __FT5206_H	
#include "DEV_Config.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//7����ݴ�����-FT5206 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/28
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//����ݴ��������ӵ�оƬ����(δ����IIC����) 
//IO��������	  
//#define FT_RST  PIout(8)//FT5206��λ����
//#define FT_INT  PHin(7) //FT5206������	

#define FT_INT					DEV_Digital_Read(CTP_EINT_PIN)
#define FT_RST(_value) 	HAL_GPIO_WritePin(CTP_RST_PIN, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)

//I2C��д����	
#define FT_CMD_WR 					0X70    //д����
#define FT_CMD_RD 					0X71		//������
  
//FT5206 ���ּĴ������� 
#define FT_DEVIDE_MODE 			0x00  	//FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER   0x02		//����״̬�Ĵ���

#define FT_TP1_REG 					0X03	  //��һ�����������ݵ�ַ
#define FT_TP2_REG 					0X09		//�ڶ������������ݵ�ַ
#define FT_TP3_REG 					0X0F		//���������������ݵ�ַ
#define FT_TP4_REG 					0X15		//���ĸ����������ݵ�ַ
#define FT_TP5_REG 					0X1B		//��������������ݵ�ַ  
 

#define	FT_ID_G_LIB_VERSION		0xA1			//�汾		
#define FT_ID_G_MODE 					0xA4   		//FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP				0x80   		//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE	0x88   		//����״̬�������üĴ���

unsigned char FT5206_WR_Reg(unsigned int reg,unsigned char *buf,unsigned char len);
void FT5206_RD_Reg(unsigned int reg,unsigned char *buf,unsigned char len);
unsigned char FT5206_Init(void);
unsigned char FT5206_Scan(unsigned char mode);

#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define CTP_DEBUG    		0
#define CTP_LOG_ERR			1
#define CTP_LOG_INFO		0


#ifndef CTP_DEBUG
#define CTP_DEBUG    0
#endif

#ifndef FT5206_LOG_PRINTF
#ifdef RT_VER_NUM
/* for RT-Thread platform */
extern void rt_kprintf(const char *fmt, ...);
#define FT5206_LOG_PRINTF rt_kprintf
#else
#define FT5206_LOG_PRINTF printf
#endif /* RT_VER_NUM */
#endif /* FT5206_LOG_PRINTF */

#if CTP_DEBUG
	#ifdef assert
		#undef assert
	#endif
	#define assert(EXPR)                                                           \
	if (!(EXPR))                                                                   \
	{                                                                              \
			FT5206_LOG_PRINTF("(%s) has assert failed at %s.\n", #EXPR, __FUNCTION__);        \
			while (1);                                                                 \
	}
	/* debug level log */
	#ifdef  FT5206_log_d
		#undef  FT5206_log_d
	#endif
	#define FT5206_log_d(...)           FT5206_LOG_PRINTF("[D][CTP] (%s:%d) ", __FUNCTION__, __LINE__);FT5206_LOG_PRINTF(__VA_ARGS__);FT5206_LOG_PRINTF("\n")
#else
	#ifdef assert
		#undef assert
	#endif
	#define assert(EXPR)                   ((void)0);

	/* debug level log */
	#ifdef  FT5206_log_d
		#undef  FT5206_log_d
	#endif
	#define FT5206_log_d(...)
#endif /* CTP_DEBUG */

#ifndef CTP_LOG_ERR
	#define CTP_LOG_ERR    0
#endif
#if CTP_LOG_ERR
	/* error level log */
	#ifdef  FT5206_log_err
	#undef  FT5206_log_err
	#endif
	#define FT5206_log_err(...)          FT5206_LOG_PRINTF("\033[31;22m[E][CTP] (%s:%d) ", __FUNCTION__, __LINE__);FT5206_LOG_PRINTF(__VA_ARGS__);FT5206_LOG_PRINTF("\033[0m\n")
#else
	/* error level log */
	#ifdef  FT5206_log_err
		#undef  FT5206_log_err
	#endif
	#define FT5206_log_err(...) 
#endif

#ifndef CTP_LOG_INFO
	#define CTP_LOG_INFO    0
#endif
#if CTP_LOG_INFO
	/* info level log */
	#ifdef  FT5206_log_info
	#undef  FT5206_log_info
	#endif
	#define FT5206_log_info(...)         FT5206_LOG_PRINTF("\033[32;22m[I][CTP] ");FT5206_LOG_PRINTF(__VA_ARGS__);FT5206_LOG_PRINTF("\033[0m\n")
#else
	/* info level log */
	#ifdef  FT5206_log_info
		#undef  FT5206_log_info
	#endif
	#define FT5206_log_info(...) 
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

















