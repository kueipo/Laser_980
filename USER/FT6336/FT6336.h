#include "i2c.h"
#include "sys.h"


#define i2c_scl    PBout(13) //SCL
#define i2c_sda    PBout(15) //SDA	 
#define i2c_sda_rd   PBin(15)  // ‰»ÎSDA 

#define LED_EN PBout(12)

void find_ic_addr(void);
void i2c_write_byte_check(unsigned char txd);
void FT6336_init(void);
u8 FT6336_read_firmware_id(void);
u8 FT6336_read_device_mode(void);
u8 FT6336_read_td_status(void);
u16 FT6336_read_touch1_x(void);
u16 FT6336_read_touch1_y(void);
u8 FT6336_read_touch1_event(void);
u8 FT6336_read_touch1_id(void);

u8 FT6336_read_touch2_event(void);
u8 FT6336_read_touch2_id(void);
u16 FT6336_read_touch2_x(void);
u16 FT6336_read_touch2_y(void);


