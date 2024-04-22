#include "ft5206.h"
#include "touch.h"
#include "ctiic.h"
#include "delay.h"
#include "LCD_2inch.h"
//#include "lcd.h"
//#include "usart.h"
//#include "delay.h" 
//#include "string.h" 
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
 
 
//��FT5206д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
unsigned char FT5206_WR_Reg(unsigned int reg,unsigned char *buf,unsigned char len)
{
	unsigned char i;
	unsigned char ret=0;
	CT_IIC_Start();	 
	CT_IIC_Send_Byte(FT_CMD_WR);	//����д���� 	 
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
//��FT5206����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void FT5206_RD_Reg(unsigned int reg,unsigned char *buf,unsigned char len)
{
	unsigned char i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(FT_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(FT_CMD_RD);   	//���Ͷ�����		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
    CT_IIC_Stop();//����һ��ֹͣ����     
} 
//��ʼ��FT5206������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
unsigned char FT5206_Init(void)
{
	unsigned char temp[2]; 
//    GPIO_InitTypeDef GPIO_Initure;
// 
//    __HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
//    __HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOIʱ��
//                
//    //PH7
//    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
//    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
//    GPIO_Initure.Pull=GPIO_PULLUP;          //����
//    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
//    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��
//            
//    //PI8
//    GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
//    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
//    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //��ʼ��
        
	CT_IIC_Init();    //��ʼ����������I2C����  
	FT_RST(0);				//��λ
	delay_ms(20);
 	FT_RST(1);				//�ͷŸ�λ		    
	delay_ms(50);  	
	temp[0]=0;
	FT5206_WR_Reg(FT_DEVIDE_MODE,temp,1);	//������������ģʽ
	FT5206_WR_Reg(FT_ID_G_MODE,temp,1);		//��ѯģʽ 
	temp[0]=22;								//������Чֵ��22��ԽСԽ����	
	FT5206_WR_Reg(FT_ID_G_THGROUP,temp,1);	//���ô�����Чֵ
	temp[0]=12;								//�������ڣ�����С��12�����14
	FT5206_WR_Reg(FT_ID_G_PERIODACTIVE,temp,1); 
	//��ȡ�汾�ţ��ο�ֵ��0x3003
	FT5206_RD_Reg(FT_ID_G_LIB_VERSION,&temp[0],2);  
	if((temp[0]==0X30&&temp[1]==0X03)||temp[1]==0X01||temp[1]==0X02)//�汾:0X3003/0X0001/0X0002
	{
		FT5206_log_d("CTP ID:%x\r\n",((unsigned int)temp[0]<<8)+temp[1]);
		return 0;
	} 
	return 1;
}
const unsigned int FT5206_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
unsigned char FT5206_Scan(unsigned char mode)
{
	unsigned char buf[4];
	unsigned char i=0;
	unsigned char res=0;
	volatile unsigned char temp;
//	static unsigned char t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
//	t++;
//	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
//	{
		FT5206_RD_Reg(FT_REG_NUM_FINGER,&mode,1);//��ȡ�������״̬  
		if((mode&0XF)&&((mode&0XF)<6))	//�д�������С��6���㣬�����֧��5�㴥��
		{
			temp=0XFF<<(mode&0XF);//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES;
		//	for(i=0;i<5;i++)
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))		//�Ƿ��д�����Ч?
				{
					FT5206_RD_Reg(FT5206_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
					if( buf[0] & 0X80 )	//������contact�¼�������Ϊ��Ч
			//		if( (buf[0] & 0XC0)==0 )	//������Put Down�¼�������Ϊ��Ч
					{
						tp_dev.x[i] = (((unsigned int)(buf[0]&0X0F)<<8)+buf[1]);
						tp_dev.y[i] = (((unsigned int)(buf[2]&0X0F)<<8)+buf[3]);
						
						if(tp_dev.x[i]<240 && tp_dev.y[i]<240)
						{
							res = 1;
							FT5206_log_d("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
						}
					}
				}			
			}
			if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//���������ݶ���0,����Դ˴�����
//			t=0;		//����һ��,��������������10��,�Ӷ����������
		}
//	}
	if((mode&0X1F)==0)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
		}else						//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������Ч���	
		}	 
	} 	
//	if(t>240)t=10;//���´�10��ʼ����
	return res;
	
}
 



























