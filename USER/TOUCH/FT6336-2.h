#include "i2c.h"
#include "sys.h"


#define i2c_scl    PBout(6) //SCL
#define i2c_sda    PBout(7) //SDA	 
#define i2c_sda_rd   PBin(7)  // ‰»ÎSDA 

#define LED_EN PBout(9)

void find_ic_addr(void);
void i2c_write_byte_check(unsigned char txd);
void FT6336_init(void);
unsigned char FT6336_read_firmware_id(void);
unsigned char FT6336_read_device_mode(void);
unsigned char FT6336_read_td_status(void);
unsigned int FT6336_read_touch1_x(void);
unsigned int FT6336_read_touch1_y(void);
unsigned char FT6336_read_touch1_event(void);
unsigned char FT6336_read_touch1_id(void);

unsigned char FT6336_read_touch2_event(void);
unsigned char FT6336_read_touch2_id(void);
unsigned int FT6336_read_touch2_x(void);
unsigned int FT6336_read_touch2_y(void);


