
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "iap/inc/iap.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */
#define TX_TIMEOUT          ((uint32_t)100)
#define RX_TIMEOUT          ((uint32_t)1500) //HAL_MAX_DELAY

/* Exported macro ------------------------------------------------------------*/
#define IS_CAP_LETTER(c)    (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)     (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)            (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c)       (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))

/* Exported functions ------------------------------------------------------- */
void Int2Str(uint8_t *p_str, uint32_t intnum);
uint32_t Str2Int(uint8_t *inputstr, uint32_t *intnum);
void Serial_PutString(char *p_string);
HAL_StatusTypeDef Serial_PutByte(uint8_t param);
void cpu_reset(void);

int Read_Flash(uint32_t addr, uint8_t *buf, size_t size);
int Write_Flash(uint32_t addr, const uint8_t *buf, size_t size);
int Erase_Flash(uint32_t addr, size_t size);

HAL_StatusTypeDef Data_Transmit(uint8_t *pData, size_t Size, uint32_t Timeout);
HAL_StatusTypeDef Data_Receive(uint8_t *pData, size_t Size, uint32_t Timeout);

#endif  /* __COMMON_H */
