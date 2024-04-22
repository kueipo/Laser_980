/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_UART_H__
#define __BSP_UART_H__

/* Includes ------------------------------------------------------------------*/
#include "sys/ringbuffer.h"

/* Exported define -----------------------------------------------------------*/
#define ENABLE_UART_0							1
	#if ENABLE_UART_0
		#define UART_HANDLE_0					&huart2
		#define ENABLE_UART_0_RX_DMA	0
			#if ENABLE_UART_0_RX_DMA
				#define UART_0_RX_DMA_CHANNEL	DMA1_Channel5_IRQn
			#endif /* ENABLE_UART_0_RX_DMA */
	#endif /* ENABLE_UART_0 */

#define ENABLE_UART_1							0
	#if ENABLE_UART_1
		#define UART_HANDLE_1					&huart1
		#define ENABLE_UART_1_RX_DMA	0
			#if ENABLE_UART_1_RX_DMA
				#define UART_1_RX_DMA_CHANNEL	DMA1_Channel5_IRQn
			#endif /* ENABLE_UART_1_RX_DMA */
	#endif /* ENABLE_UART_1 */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Uart Tag */
typedef struct
{
	UART_HandleTypeDef *huart;
	IRQn_Type DMAIRQn;
	uint8_t Rx_size;
	uint8_t Tx_size;
	uint8_t *Rx_buffer;
	uint8_t *Tx_buffer;
	struct ring_buffer *Rx_ring_buffer_p;
	struct ring_buffer *Tx_ring_buffer_p;
}BSP_UART_CONFIG;

/* FREQ Num */
typedef enum
{
  UART_0 = 0x00,
	
#if ENABLE_UART_1
	UART_1,
#endif /* ENABLE_UART_1 */

  UART_ID_MAX,
}ENUM_UART_INDEX_BSP;

extern const BSP_UART_CONFIG g_stUartCfg[];

/* External functions --------------------------------------------------------*/
void BSP_Uart_Init(void);
void BSP_Uart_DeInit(void);
void BSP_Uart_Enable(uint8_t ucIndex);
void BSP_Uart_EnableDMA(uint8_t ucIndex);
void BSP_UART_RxData(UART_HandleTypeDef *huart, uint8_t *p, uint8_t size);
void BSP_UART_TxDataToID(uint8_t UartID, uint8_t *p, uint8_t size);
void BSP_UART_TxData(UART_HandleTypeDef *huart, uint8_t *p, uint8_t size);
void BSP_UART_TxStart(UART_HandleTypeDef *huart);
uint8_t BSP_UART_IdSearch(UART_HandleTypeDef *huart);
uint8_t * BSP_UART_GetBuff(UART_HandleTypeDef *huart);
uint8_t BSP_UART_GetBuffSize(UART_HandleTypeDef *huart);
void BSP_UART_Receive(UART_HandleTypeDef *huart);

#endif /* __BSP_UART_H__ */
