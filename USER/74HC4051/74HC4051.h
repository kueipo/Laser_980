#ifndef _CD74HC4051_H_
#define _CD74HC4051_H_

#define CD74HC4051_CHANNEL_0 (unsigned char)0X00
#define CD74HC4051_CHANNEL_1 (unsigned char)0X01
#define CD74HC4051_CHANNEL_2 (unsigned char)0X02
#define CD74HC4051_CHANNEL_3 (unsigned char)0X03
#define CD74HC4051_CHANNEL_4 (unsigned char)0X04
#define CD74HC4051_CHANNEL_5 (unsigned char)0X05
#define CD74HC4051_CHANNEL_6 (unsigned char)0X06
#define CD74HC4051_CHANNEL_7 (unsigned char)0X07

void CD74HC4051_Init(void);
void CD74HC4051_Channel(unsigned char Channel);

#endif /* _CD74HC4051_H_ */
