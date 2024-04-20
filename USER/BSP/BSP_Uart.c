
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Define --------------------------------------------------------------------*/
#define RX_LENGTH_0				128
#define TX_LENGTH_0				128

#define RX_LENGTH_1				32
#define TX_LENGTH_1				32

#define RX_LENGTH_2				32
#define TX_LENGTH_2				32

#define RX_LENGTH_3				32
#define TX_LENGTH_3				32

#define RX_LENGTH_4				32
#define TX_LENGTH_4				32

/* Variables -----------------------------------------------------------------*/
/* UART_0 ------------------------------------------- */
uint8_t RxBuffer0[RX_LENGTH_0] = {0};
#if ENABLE_UART_0_RX_DMA
uint8_t RxUartBuffer0[RX_LENGTH_0] = {0};
#endif

struct ring_buffer s_stRx_RingBuffer0 = 
{
	.in = 0,
	.out = 0,
	.size = RX_LENGTH_0,
	.buf = RxBuffer0,
};

uint8_t TxBuffer0[TX_LENGTH_0] = {0};
uint8_t TxUartBuffer0[TX_LENGTH_0] = {0};
struct ring_buffer s_stTx_RingBuffer0 = 
{
	.in = 0,
	.out = 0,
	.size = TX_LENGTH_0,
	.buf = TxBuffer0,
};

/* UART_1 ------------------------------------------- */
#if ENABLE_UART_1
uint8_t RxBuffer1[RX_LENGTH_1] = {0};
#if ENABLE_UART_1_RX_DMA
uint8_t RxUartBuffer1[RX_LENGTH_1] = {0};
#endif
struct ring_buffer s_stRx_RingBuffer1 = 
{
	.in = 0,
	.out = 0,
	.size = RX_LENGTH_1,
	.buf = RxBuffer1,
};

uint8_t TxBuffer1[TX_LENGTH_1] = {0};
uint8_t TxUartBuffer1[TX_LENGTH_1] = {0};
struct ring_buffer s_stTx_RingBuffer1 = 
{
	.in = 0,
	.out = 0,
	.size = TX_LENGTH_1,
	.buf = TxBuffer1,
};
#endif
/* UART_2 ------------------------------------------- */
#if ENABLE_UART_2
uint8_t RxBuffer2[RX_LENGTH_2] = {0};
#if ENABLE_UART_2_RX_DMA
uint8_t RxUartBuffer2[RX_LENGTH_2] = {0};
#endif
struct ring_buffer s_stRx_RingBuffer2 = 
{
	.in = 0,
	.out = 0,
	.size = RX_LENGTH_2,
	.buf = RxBuffer2,
};

uint8_t TxBuffer2[TX_LENGTH_2] = {0};
uint8_t TxUartBuffer2[TX_LENGTH_2] = {0};
struct ring_buffer s_stTx_RingBuffer2 = 
{
	.in = 0,
	.out = 0,
	.size = TX_LENGTH_2,
	.buf = TxBuffer2,
};
#endif
/* UART_3 ------------------------------------------- */
#if ENABLE_UART_3
uint8_t RxBuffer3[RX_LENGTH_3] = {0};
#if ENABLE_UART_3_RX_DMA
uint8_t RxUartBuffer3[RX_LENGTH_3] = {0};
#endif
struct ring_buffer s_stRx_RingBuffer3 = 
{
	.in = 0,
	.out = 0,
	.size = RX_LENGTH_3,
	.buf = RxBuffer3,
};

uint8_t TxBuffer3[TX_LENGTH_3] = {0};
uint8_t TxUartBuffer3[TX_LENGTH_3] = {0};
struct ring_buffer s_stTx_RingBuffer3 = 
{
	.in = 0,
	.out = 0,
	.size = TX_LENGTH_3,
	.buf = TxBuffer3,
};
#endif
/* UART_4 ------------------------------------------- */
#if ENABLE_UART_4
uint8_t RxBuffer4[RX_LENGTH_4] = {0};
#if ENABLE_UART_4_RX_DMA
uint8_t RxUartBuffer4[RX_LENGTH_4] = {0};
#endif
struct ring_buffer s_stRx_RingBuffer4 = 
{
	.in = 0,
	.out = 0,
	.size = RX_LENGTH_4,
	.buf = RxBuffer4,
};

uint8_t TxBuffer4[TX_LENGTH_4] = {0};
uint8_t TxUartBuffer4[TX_LENGTH_4] = {0};
struct ring_buffer s_stTx_RingBuffer4 = 
{
	.in = 0,
	.out = 0,
	.size = TX_LENGTH_4,
	.buf = TxBuffer4,
};
#endif
/* Configuration table -------------------------------------------------------*/
const BSP_UART_CONFIG g_stUartCfg[UART_ID_MAX] = 
{
  /******* UART_0 ***********/
  {
		.huart = UART_HANDLE_0,
			
#if ENABLE_UART_0_RX_DMA
		.DMAIRQn = UART_0_RX_DMA_CHANNEL,
		.Rx_size = RX_LENGTH_0,
		.Rx_buffer = RxUartBuffer0,
#endif /* ENABLE_UART_0_RX_DMA */
		.Rx_ring_buffer_p = &s_stRx_RingBuffer0,
		
		.Tx_size = TX_LENGTH_0,
		.Tx_buffer = TxUartBuffer0,
		.Tx_ring_buffer_p = &s_stTx_RingBuffer0,
  },
	/******* UART_1 ***********/
#if ENABLE_UART_1
	{
		.huart = UART_HANDLE_1,
		
#if ENABLE_UART_1_RX_DMA
		.DMAIRQn = UART_1_RX_DMA_CHANNEL,
		.Rx_size = RX_LENGTH_1,
		.Rx_buffer = RxUartBuffer1,
#endif /* ENABLE_UART_1_RX_DMA */
		.Rx_ring_buffer_p = &s_stRx_RingBuffer1,
		
		.Tx_size = TX_LENGTH_1,
		.Tx_buffer = TxUartBuffer1,
		.Tx_ring_buffer_p = &s_stTx_RingBuffer1,
	},
#endif /* ENABLE_UART_1 */
	/******* UART_2 ***********/
#if ENABLE_UART_2
	{
		.huart = UART_HANDLE_2,

#if ENABLE_UART_2_RX_DMA
		.DMAIRQn = UART_2_RX_DMA_CHANNEL,
		.Rx_size = RX_LENGTH_2,
		.Rx_buffer = RxUartBuffer2,
#endif /* ENABLE_UART_2_RX_DMA */
		.Rx_ring_buffer_p = &s_stRx_RingBuffer2,
		
		.Tx_size = TX_LENGTH_2,
		.Tx_buffer = TxUartBuffer2,
		.Tx_ring_buffer_p = &s_stTx_RingBuffer2,
	},
#endif /* ENABLE_UART_2 */
	/******* UART_3 ***********/
#if ENABLE_UART_3
	{
		.huart = UART_HANDLE_3,
		
#if ENABLE_UART_3_RX_DMA
		.DMAIRQn = UART_3_RX_DMA_CHANNEL,
		.Rx_size = RX_LENGTH_3,
		.Rx_buffer = RxUartBuffer3,
#endif /* ENABLE_UART_3_RX_DMA */
		.Rx_ring_buffer_p = &s_stRx_RingBuffer3,
		
		.Tx_size = TX_LENGTH_3,
		.Tx_buffer = TxUartBuffer3,
		.Tx_ring_buffer_p = &s_stTx_RingBuffer3,
	},
#endif /* ENABLE_UART_3 */
	/******* UART_4 ***********/
#if ENABLE_UART_4
	{
		.huart = UART_HANDLE_4,
		
#if ENABLE_UART_4_RX_DMA
		.DMAIRQn = UART_4_RX_DMA_CHANNEL,	
		.Rx_size = RX_LENGTH_4,
		.Rx_buffer = RxUartBuffer4,
#endif /* ENABLE_UART_4_RX_DMA */
		.Rx_ring_buffer_p = &s_stRx_RingBuffer4,
		
		.Tx_size = TX_LENGTH_4,
		.Tx_buffer = TxUartBuffer4,
		.Tx_ring_buffer_p = &s_stTx_RingBuffer4,
	},
#endif /* ENABLE_UART_4 */
};

/**
 * @brief  BSP_Uart_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Uart_Init(void)
{
	uint8_t index;

	for (index = 0; index < UART_ID_MAX; index++)
		BSP_Uart_Enable(index);

#if ENABLE_UART_0_RX_DMA
	BSP_Uart_EnableDMA(UART_0);
#endif
#if ENABLE_UART_1_RX_DMA
	BSP_Uart_EnableDMA(UART_1);
#endif
#if ENABLE_UART_2_RX_DMA
	BSP_Uart_EnableDMA(UART_2);
#endif
#if ENABLE_UART_3_RX_DMA
	BSP_Uart_EnableDMA(UART_3);
#endif
#if ENABLE_UART_4_RX_DMA
	BSP_Uart_EnableDMA(UART_4);
#endif
}

/**
 * @brief  BSP_Uart_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Uart_DeInit(void)
{
}

/**
 * @brief  BSP_Uart_Enable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Uart_Enable(uint8_t id)
{
	UART_HandleTypeDef *huart;

	huart = g_stUartCfg[id].huart;

	__HAL_UART_ENABLE_IT(huart, UART_IT_PE);
	__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);
	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

/**
 * @brief  BSP_Uart_EnableDMA.
 * @note   None.
 * @param  ucIndex.
 * @retval None.
 */
void BSP_Uart_EnableDMA(uint8_t id)
{
	UART_HandleTypeDef *huart;
	uint8_t *buf;
	uint8_t size;

	huart = g_stUartCfg[id].huart;
	buf = g_stUartCfg[id].Rx_buffer;
	size = g_stUartCfg[id].Rx_size;

#if 1
	IRQn_Type DMAIRQn;
	DMAIRQn = g_stUartCfg[id].DMAIRQn;
	/* Disables a device specific interrupt in the NVIC interrupt controller. */
	HAL_NVIC_DisableIRQ(DMAIRQn);
#endif

#if 1
	/* Disables interrupt */
	__HAL_UART_DISABLE_IT(huart, UART_IT_PE);
	__HAL_UART_DISABLE_IT(huart, UART_IT_ERR);
	__HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);
#endif

	/* Enable the specified UART interrupt. */
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
	/* Receives an amount of data in DMA mode. */
	HAL_UART_Receive_DMA(huart, buf, size);
}

/**
 * @brief  BSP_UART_RxData.
 * @note   None.
 * @param  huart.
 * @param  p.
 * @param  size.
 * @retval None.
 */
void BSP_UART_RxData(UART_HandleTypeDef *huart, uint8_t *p, uint8_t size)
{
	uint8_t index = BSP_UART_IdSearch(huart);
	if (index < UART_ID_MAX)
		RingBufferPut(g_stUartCfg[index].Rx_ring_buffer_p, p, size);
}

/**
 * @brief  BSP_UART_TxDataToID.
 * @note   None.
 * @param  UartID.
			 p.
			 size.
 * @retval None.
 */
void BSP_UART_TxDataToID(uint8_t id, uint8_t *p, uint8_t size)
{
	if (id >= UART_ID_MAX)
		return;

	UART_HandleTypeDef *huart = g_stUartCfg[id].huart;

	RingBufferPut(g_stUartCfg[id].Tx_ring_buffer_p, p, size);

	BSP_UART_TxStart(huart);
}

/**
 * @brief  BSP_UART_TxData.
 * @note   None.
 * @param  huart.
 * @param	 p.
 * @param	 size.
 * @retval None.
 */
void BSP_UART_TxData(UART_HandleTypeDef *huart, uint8_t *p, uint8_t size)
{
	uint8_t index = BSP_UART_IdSearch(huart);

	BSP_UART_TxDataToID(index, p, size);
}

/**
 * @brief  BSP_UART_TxStart.
 * @note   None.
 * @param  huart.
 * @retval None.
 */
void BSP_UART_TxStart(UART_HandleTypeDef *huart)
{
	uint8_t index;
	uint16_t length;

	if (huart->gState == HAL_UART_STATE_READY)
	{
		index = BSP_UART_IdSearch(huart);
		if (index < UART_ID_MAX)
		{
			length = GetRingBufferLen(g_stUartCfg[index].Tx_ring_buffer_p);
			if (length) /* NOT EMPTY */
			{
				if (length > g_stUartCfg[index].Tx_size)
					length = g_stUartCfg[index].Tx_size;

				RingBufferGet(g_stUartCfg[index].Tx_ring_buffer_p, g_stUartCfg[index].Tx_buffer, length);
#if 0	
				if (HAL_UART_Transmit_DMA(huart, g_stUartCfg[index].Tx_buffer, length) == HAL_BUSY)
#else
				if (HAL_UART_Transmit_IT(huart, g_stUartCfg[index].Tx_buffer, length) == HAL_BUSY)
				{
					HAL_UART_AbortTransmit(huart);
				}
#endif
			}
		}
	}
}

/**
 * @brief  BSP_UART_IdSearch.
 * @note   None.
 * @param  huart.
 * @retval ID.
 */
uint8_t BSP_UART_IdSearch(UART_HandleTypeDef *huart)
{
	uint8_t index;
	for (index = 0; index < UART_ID_MAX; index++)
	{
		if (g_stUartCfg[index].huart == huart)
			return index;
	}
	return 0xFF;
}

/**
 * @brief  BSP_UART_GetBuff.
 * @note   None.
 * @param  id.
 * @retval buff pointer.
 */
uint8_t *BSP_UART_GetBuff(UART_HandleTypeDef *huart)
{
	uint8_t id = BSP_UART_IdSearch(huart);

	if (id >= UART_ID_MAX)
		return g_stUartCfg[0].Rx_buffer;

	return g_stUartCfg[id].Rx_buffer;
}

/**
 * @brief  BSP_UART_GetBuffSize.
 * @note   None.
 * @param  huart.
 * @retval size.
 */
uint8_t BSP_UART_GetBuffSize(UART_HandleTypeDef *huart)
{
	uint8_t id = BSP_UART_IdSearch(huart);

	if (id >= UART_ID_MAX)
		return 0;

	return g_stUartCfg[id].Rx_size;
}

/**
 * @brief  BSP_UART_Receive.
 * @note   None.
 * @param  huart.
 * @retval None.
 */
void BSP_UART_Receive(UART_HandleTypeDef *huart)
{
	uint8_t ch = (uint8_t)(huart->Instance->DR & 0x00FF);
	BSP_UART_RxData(huart, &ch, 1);
}
