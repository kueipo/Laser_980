/* Includes ------------------------------------------------------------------*/
#include "myupdate.h"
#include "common.h"
#include "flash_if.h"
#include "main.h"
#include "menu.h"
#include "string.h"
#include "usart.h"
#include "ymodem.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RETRY_TIMES 10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void my_Receive(void)
{
	unsigned char char1 = 0;
	char tmp[] = "NX\r\n";
	char tmp1[] = "FL\r\n";
	unsigned char failtimes = 0;
	HAL_StatusTypeDef status;
	uint32_t packet_length = 1024;
	uint8_t aPacketData[1024];
	uint32_t flashdestination, ramsource;
	flashdestination = APPLICATION_ADDRESS;
	FLASH_If_Erase(APPLICATION_ADDRESS);
	while (1)
	{
		status = HAL_UART_Receive(g_huart, &char1, 1, DOWNLOAD_TIMEOUT * 2);
		if (status == HAL_OK)
		{
			if (char1 == 'N')
			{
				status = HAL_UART_Receive(g_huart, aPacketData, 1024, DOWNLOAD_TIMEOUT * 10);
				if (status == HAL_OK)
				{
					ramsource = (uint32_t)&aPacketData[0];

					/* Write received data in Flash */
					if (FLASH_If_Write(flashdestination, (uint32_t *)ramsource, packet_length / 4) == FLASHIF_OK)
					{
						flashdestination += packet_length;
						HAL_UART_Transmit(g_huart, (unsigned char *)tmp, 4, NAK_TIMEOUT);
					}
				}
				else
				{
					HAL_UART_Transmit(g_huart, (unsigned char *)tmp1, 4, NAK_TIMEOUT);
					if (++failtimes > RETRY_TIMES)
						cpu_reset();
				}
			}
			else if (char1 == 'E')
			{
				HAL_Delay(500);
				Execute_Application();
			}
			else if (char1 == 'R')
			{
				HAL_Delay(500);
				FLASH_If_Erase(APPLICATION_ADDRESS);
				HAL_Delay(500);
				flashdestination = APPLICATION_ADDRESS;
				HAL_UART_Transmit(g_huart, (unsigned char *)tmp, 4, NAK_TIMEOUT);
			}
		}
		else
			HAL_UART_Transmit(g_huart, (unsigned char *)tmp, 4, NAK_TIMEOUT);
	}
}
