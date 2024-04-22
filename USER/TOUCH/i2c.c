//**************************************************************************
// I2C���߲���
//**************************************************************************
// #include "head.h"
// #include "sys.h"
#include "i2c.h"
#include "delay.h"
// #include "lcd.h"
#include "stm32f10x.h"

#ifdef NCPL
#define i2c_scl PBout(13)	// SCL
#define i2c_sda PBout(15)	// SDA
#define i2c_sda_rd PBin(15) // ����SDA

delay_init();

void i2c_init(void)
{

	RCC->APB2ENR |= 1 << 3; // ��ʹ������IO PORTAʱ��
	GPIOB->CRH &= 0XFF0FFFFF;
	GPIOB->CRH |= 0X00300000;

	GPIOB->CRH &= 0X0FFFFFFF;
	GPIOB->CRH |= 0X30000000;

	GPIOB->ODR = 0XFFFFFFFF;

#ifdef channel_16
	// PA1 SCL_2
	RCC->APB2ENR |= 1 << 2; // ʹ������IO PORTAʱ��
	GPIOB->CRL &= 0XFFFFFF0F;
	GPIOB->CRL |= 0X00000030;
#endif
}

void i2c_sda_in(void)
{
	GPIOB->CRH &= 0X0FFFFFFF;
	GPIOB->CRH |= 0X80000000;
}

void i2c_sda_out(void)
{
	GPIOB->CRH &= 0X0FFFFFFF;
	GPIOB->CRH |= 0X30000000;
}

#else
#define i2c_scl PBout(13)	// SCL
#define i2c_sda PBout(15)	// SDA
#define i2c_sda_rd PBin(15) // ����SDA

void i2c_init(void)
{
	RCC->APB2ENR |= 1 << 3; // ��ʹ������IO PORTBʱ��
	GPIOB->CRH &= 0X0F0FFFFF;
	GPIOB->CRH |= 0X30300000;
	GPIOB->ODR = 0XFFFFFFFF;
}

void i2c_sda_in(void)
{
	GPIOB->CRH &= 0X0F0FFFFF;
	GPIOB->CRH |= 0X80300000;
}

void i2c_sda_out(void)
{
	GPIOB->CRL &= 0X0F0FFFFF;
	GPIOB->CRL |= 0X30300000;
}
#endif

//-------------------------------�ָ�Ʋ���-----------------------
void i2c_start(void)
{
	i2c_sda_out(); // sda�����
	i2c_sda = 1;
	i2c_scl = 1;
	delay_us(10); // 8ͨ��ʱ,5us����,16ͨ��ʱ,�����������½�,������Ҫ8us,Ϊ�˱�֤û������10us
	i2c_sda = 0;  // START:when i2c is high,DATA change form high to low
	delay_us(10);
	i2c_scl = 0; // ǯסI2C���ߣ�׼�����ͻ��������
}

void i2c_end(void)
{
	i2c_sda_out(); // sda�����
	i2c_scl = 0;
	i2c_sda = 0; // STOP:when i2c is high DATA change form low to high
	delay_us(10);
	i2c_scl = 1;
	i2c_sda = 1; // ����I2C���߽����ź�
	delay_us(10);
}

void i2c_write_byte(unsigned char txd)
{
	u8 t;
	i2c_sda_out();
	i2c_scl = 0; // ����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		i2c_sda = (txd & 0x80) >> 7;
		txd <<= 1;
		delay_us(10); // ��TEA5767��������ʱ���Ǳ����
		i2c_scl = 1;
		delay_us(10);
		i2c_scl = 0;
		delay_us(10);
	}
	i2c_sda = 1;
	delay_us(10);
	i2c_sda_in();
	i2c_scl = 1;
	delay_us(10);
	//	while(i2c_sda_rd);
	for (t = 0; t < 100; t++) // ��ʱ100us�ȴ�
		if (i2c_sda_rd)
			delay_us(1);
		else
			break;
	i2c_scl = 0;

	//----------------------------������ʾ--------------------
	if (t >= 100)
		// string_normal(DIS_COL_BOUNDARY+1,UP_START+1,Red,"I2C_NCPL ERROR!");
		;
}

unsigned char i2c_read_byte(void)
{
	unsigned char i, receive = 0;
	i2c_sda_in(); // SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		i2c_scl = 0;
		delay_us(10);
		i2c_scl = 1;
		receive <<= 1;
		if (i2c_sda_rd)
			receive++;
		delay_us(10);
	}
	//    	if (!ack)
	//        {
	i2c_scl = 0;
	i2c_sda_out();
	i2c_sda = 1;
	delay_us(10);
	i2c_scl = 1;
	delay_us(10);
	i2c_scl = 0;
	//		}
	//
	//		 else
	//        {
	//			i2c_scl=0;
	//			i2c_sda_out();
	//			i2c_sda=0;
	//			delay_us_int(10);
	//			i2c_scl=1;
	//			delay_us_int(10);
	//			i2c_scl=0;
	//		}
	i2c_sda = 1;
	return receive;
}

unsigned char i2c_read_keep_byte(void)
{
	unsigned char i, receive = 0;
	i2c_sda_in(); // SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		i2c_scl = 0;
		delay_us(10);
		i2c_scl = 1;
		receive <<= 1;
		if (i2c_sda_rd)
			receive++;
		delay_us(10);
	}
	i2c_scl = 0;
	i2c_sda_out();
	i2c_sda = 0;
	delay_us(10);
	i2c_scl = 1;
	delay_us(10);
	i2c_scl = 0;
	i2c_sda = 1;
	return receive;
}

unsigned char i2c_read_addr_byte(unsigned char device_addr, unsigned char read_addr)
{
	unsigned char dat;
	i2c_start();
	i2c_write_byte(device_addr << 1);
	i2c_write_byte(read_addr);
	i2c_end();

	i2c_start();
	i2c_write_byte((device_addr << 1) | 0x01);
	dat = i2c_read_byte();
	i2c_end();
	return (dat);
}

void i2c_read_addr_str(unsigned char device_addr, unsigned char read_addr, unsigned char read_amount, unsigned char *read_buf)
{
	unsigned char i;
	i2c_start();
	i2c_write_byte(device_addr << 1);
	i2c_write_byte(read_addr);
	i2c_end();

	i2c_start();
	i2c_write_byte((device_addr << 1) | 0x01);

	for (i = 0; i < read_amount - 1; i++)
		read_buf[i] = i2c_read_keep_byte();
	read_buf[i] = i2c_read_byte();
	i2c_end();
}

void i2c_write_addr_byte(unsigned char device_addr, unsigned char write_addr, unsigned char write_dat)
{
	i2c_start();
	i2c_write_byte(device_addr << 1);
	i2c_write_byte(write_addr);
	i2c_write_byte(write_dat);
	i2c_end();
	delay_ms(2);
}

unsigned int i2c_read_addr_int(unsigned char device_addr, unsigned char read_addr)
{
	unsigned char read_buf[2];
	i2c_read_addr_str(device_addr, read_addr, 2, read_buf);
	return (read_buf[0] << 8) | read_buf[1];
}

void i2c_write_addr_str(unsigned char device_addr, unsigned char write_addr, unsigned char write_amount, unsigned char *write_buf)
{
	unsigned char i;
	i2c_start();
	i2c_write_byte(device_addr << 1);
	i2c_write_byte(write_addr);
	for (i = 0; i < write_amount; i++)
		i2c_write_byte(write_buf[i]);
	i2c_end();
	delay_ms(2);
}
