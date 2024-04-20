#include "FT6336.h"
//#include "LCD.h"
#include "delay.h"
#include "i2c.h"

#define I2C_ADDR_FT6336 0x38

//---------------------------------------------------------------------------------------------------
//#define LED_EN PBout(12)//RST信号

void FT6336_init(void)
{
 	//GPIO_InitTypeDef  GPIO_InitStructure;	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	
//	RCC->APB2ENR|=1<<3;		//先使能外设IO PORTB时钟 							 
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

//第一触点
unsigned char FT6336_read_touch1_event(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH1_EVENT)>>4;
}

unsigned char FT6336_read_touch1_id(void)
{
	return i2c_read_addr_byte(I2C_ADDR_FT6336,FT6336_ADDR_TOUCH1_ID)>>4;
}

//左下角为坐标零点,水平Y轴,垂直X轴
//Y轴范围0~459
//X轴范围0~319
//touch1和touch2排列顺序为按面积排列,而ID号为按下的时间先后标号,该标号可代表按下的手指
//在第一点按下后ID记为0,事件为8,而抬起后ID与坐标保持最后数值,事件为4,此时第二个点数据一直为FF
//在第一点按下前提下按第二个点,ID记为1,事件为8,抬起后全恢复FF,而当第二个点的接触面积大于第一个点时,
//它将保持ID与坐标前提下与第一个点更换存储地址,第一个点抬起后,第二个点的依旧ID为1
//按下第三个点时,将与其它两个点进行面积对比后,直接抛弃面积最小的点
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

//第二触点
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



