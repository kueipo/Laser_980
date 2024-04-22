#include "FT6336.h"
//#include "LCD.h"
#include "delay.h"
#include "i2c.h"

#define I2C_ADDR_FT6336 0x38

//---------------------------------------------------------------------------------------------------
//#define LED_EN PBout(12)//RST�ź�

void FT6336_init(void)
{
 	//GPIO_InitTypeDef  GPIO_InitStructure;	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	
//	RCC->APB2ENR|=1<<3;		//��ʹ������IO PORTBʱ�� 							 
//	GPIOB->CRH&=0XFFF0FFFF;
//	GPIOB->CRH|=0X00030000;	   
	LED_EN = 1;
	delay_ms(50);
	LED_EN = 0;
	delay_ms(50);
	LED_EN = 1;
	delay_ms(50);
}
#define FT6336_ADDR_DEVICE_MODE 	0x00
#define FT6336_ADDR_TD_STATUS 		0x02
#define FT6336_ADDR_TOUCH1_EVENT 	0x03
#define FT6336_ADDR_TOUCH1_ID 		0x05
#define FT6336_ADDR_TOUCH1_X 		0x03
#define FT6336_ADDR_TOUCH1_Y 		0x05

#define FT6336_ADDR_TOUCH2_EVENT 	0x09
#define FT6336_ADDR_TOUCH2_ID 		0x0B
#define FT6336_ADDR_TOUCH2_X 		0x09
#define FT6336_ADDR_TOUCH2_Y 		0x0B

#define FT6336_ADDR_FIRMARE_ID 		0xA6

unsigned char FT6336_read_firmware_id(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_FIRMARE_ID);
}

unsigned char FT6336_read_device_mode(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_DEVICE_MODE);
}

unsigned char FT6336_read_td_status(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TD_STATUS);
}

//��һ����
unsigned char FT6336_read_touch1_event(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH1_EVENT)>>4;
}

unsigned char FT6336_read_touch1_id(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH1_ID)>>4;
}

//���½�Ϊ�������,ˮƽY��,��ֱX��
//Y�᷶Χ0~459
//X�᷶Χ0~319
//touch1��touch2����˳��Ϊ���������,��ID��Ϊ���µ�ʱ���Ⱥ���,�ñ�ſɴ����µ���ָ
//�ڵ�һ�㰴�º�ID��Ϊ0,�¼�Ϊ8,��̧���ID�����걣�������ֵ,�¼�Ϊ4,��ʱ�ڶ���������һֱΪFF
//�ڵ�һ�㰴��ǰ���°��ڶ�����,ID��Ϊ1,�¼�Ϊ8,̧���ȫ�ָ�FF,�����ڶ�����ĽӴ�������ڵ�һ����ʱ,
//��������ID������ǰ�������һ��������洢��ַ,��һ����̧���,�ڶ����������IDΪ1
//���µ�������ʱ,���������������������ԱȺ�,ֱ�����������С�ĵ�
unsigned int FT6336_read_touch1_x(void)
{
	unsigned char read_buf[2];
	i2c_read_addr_str(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH1_X,2,read_buf);
	return ((read_buf[0]&0x0f)<<8)|read_buf[1];
}

unsigned int FT6336_read_touch1_y(void)
{
	unsigned char read_buf[2];
	i2c_read_addr_str(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH1_Y,2,read_buf);
	return ((read_buf[0]&0x0f)<<8)|read_buf[1];
}

//�ڶ�����
unsigned char FT6336_read_touch2_event(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH2_EVENT)>>4;
}

unsigned char FT6336_read_touch2_id(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH2_ID)>>4;
}

unsigned int FT6336_read_touch2_x(void)
{
	unsigned char read_buf[2];
	i2c_read_addr_str(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH2_X,2,read_buf);
	return ((read_buf[0]&0x0f)<<8)|read_buf[1];
}

unsigned int FT6336_read_touch2_y(void)
{
	unsigned char read_buf[2];
	i2c_read_addr_str(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH2_Y,2,read_buf);
	return ((read_buf[0]&0x0f)<<8)|read_buf[1];
}



