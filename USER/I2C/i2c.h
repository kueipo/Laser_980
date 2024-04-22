//#include "lcd.h"


//I2C总线函数
void i2c_init(void);

void i2c_start(void);
void i2c_end(void);
void i2c_write_byte(unsigned char temp);
unsigned char i2c_read_byte(void);
unsigned char i2c_read_keep_byte(void);

unsigned char i2c_read_addr_byte(unsigned char device_addr,unsigned char read_addr);
void i2c_write_addr_byte(unsigned char device_addr,unsigned char write_addr,unsigned char write_dat);

void i2c_read_addr_str(unsigned char device_addr,unsigned char read_addr,unsigned char read_amount,unsigned char *read_buf);

unsigned int i2c_read_addr_int(unsigned char device_addr,unsigned char read_addr);

void i2c_write_addr_str(unsigned char device_addr,unsigned char write_addr,unsigned char write_amount,unsigned char *write_buf);

void i2c_sda_in(void);
void i2c_sda_out(void);


//第二条总线

void i2c_2_init(void);

void i2c_2_start(void);//i2c_2_start()
void i2c_2_end(void);//i2c_2_end()
void i2c_2_write_byte(unsigned char temp);//i2c_2_write_byte(unsigned char temp)
unsigned char i2c_2_read_byte(void);//i2c_2_read_byte()
unsigned char i2c_2_read_keep_byte(void);//i2c_2_read_keep_byte()


