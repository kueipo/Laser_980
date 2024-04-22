
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT5466_H_
#define __FT5466_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
/* Exported macro ------------------------------------------------------------*/
//REGISTER ADDRESSES
#define FT_ADDRESS 0x70

//FT5466 ���ּĴ������� 
#define FT_DEVIDE_MODE 			0x00   		//FT5466ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER       0x02		//����״̬�Ĵ���

#define FT_TP1_REG 				0X03	  	//��һ�����������ݵ�ַ
#define FT_TP2_REG 				0X09		//�ڶ������������ݵ�ַ
#define FT_TP3_REG 				0X0F		//���������������ݵ�ַ
#define FT_TP4_REG 				0X15		//���ĸ����������ݵ�ַ
#define FT_TP5_REG 				0X1B		//��������������ݵ�ַ  
 
#define	FT_ID_G_LIB_VERSION		0xA1		//�汾		
#define FT_ID_G_MODE 			0xA4   		//FT5466�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP			0x80   		//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE	0x88   		//����״̬�������üĴ���

/* Commands for REG_COMMAND */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	FT5466_OK = 0,
	FT5466_Error = 1,
	FT5466_NotResponse = 2
} FT5466_Status_t;

typedef struct
{
	int16_t x;
	int16_t y;
} TouchCordinate_t;

/* Exported variables --------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
FT5466_Status_t FT5466_Init(void);
bool FT5466_ReadTouch(TouchCordinate_t *cordinate, uint8_t *number_of_cordinate);
bool FT5466_Read_xy(int16_t * x, int16_t * y);
void FT5466_TouchTrigger(void);
bool FT5466_IsTrigger(void);

//User method implementation prototype ----------------------------------------*/
void FT5466_RST_Control(bool high_or_low);
void FT5466_Delay(uint16_t ms);
FT5466_Status_t FT5466_I2C_Init(void);
FT5466_Status_t FT5466_I2C_Write(uint8_t Addr, uint8_t *write_data, uint16_t write_length);
FT5466_Status_t FT5466_I2C_Read(uint8_t Addr, uint8_t *read_data, uint16_t read_length);

#endif /* __FT5466_H_ */
