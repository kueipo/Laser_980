
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define ONCE_SAND_MAX		32

#define TXBUFFERSIZE_0		128
#define RXBUFFERSIZE_0		64

#define SEND_LENGTH			1

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
//uint8_t aTxFIFOBuffer_0[TXBUFFERSIZE_0];
//struct ringbuffer	TxFifo_0;

//uint8_t aRxFIFOBuffer_0[RXBUFFERSIZE_0];
//struct ringbuffer	RxFifo_0;

//DataComm_Struct CommPortTcb[COMM_PORT_MAX] = 
//{
//	{
//		.pFifo = &TxFifo_0,
//		.huart = DEV_MAIN_PORT,
//	},
//	{
//		.pFifo = &RxFifo_0,
//		.huart = DEV_MAIN_PORT,
//	}
//};

//uint8_t TxDataTemp[ONCE_SAND_MAX] = {0};
//uint8_t RxDataTemp[RXBUFFERSIZE_0] = {0};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_DataComm_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_DataComm_Init(void)
{
//	UART_HandleTypeDef  *huart = CommPortTcb[COMM_P_0_RX].huart;
//	
//	struct ringbuffer	*pFifo;
//	
//	pFifo = CommPortTcb[COMM_P_0_TX].pFifo;
//	ringbuffer_init(pFifo, aTxFIFOBuffer_0, sizeof(aTxFIFOBuffer_0));
//	
//	pFifo = CommPortTcb[COMM_P_0_RX].pFifo;
//	ringbuffer_init(pFifo, aRxFIFOBuffer_0, sizeof(aRxFIFOBuffer_0));
//	
//	__HAL_UART_ENABLE_IT(huart, UART_IT_PE);
//	__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);
//	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

/**
 * @brief  APP_WriteData.
 * @note   None.
 * @param  PortIndex.
 * @param  ptr.
 * @param  length.
 * @retval size.
 */
uint16_t APP_WriteData(ENUM_DATA_COMM_PORT PortIndex,
						const uint8_t     *ptr,
						uint16_t          length)
{
//	struct ringbuffer	*pFifo = CommPortTcb[PortIndex].pFifo;
//	
//	return ringbuffer_put_force(pFifo, ptr, length);
	return 0;
}

/**
 * @brief  APP_ReadData.
 * @note   None.
 * @param  PortIndex.
 * @param  ptr.
 * @param  length.
 * @retval size.
 */
uint16_t APP_ReadData(ENUM_DATA_COMM_PORT PortIndex,
						uint8_t     	  *ptr,
						uint16_t          length)
{
//	uint16_t size;
//	struct ringbuffer	*pFifo = CommPortTcb[PortIndex].pFifo;
//	
//	size = ringbuffer_get(pFifo, ptr, length);
//	
//	return size;
	return 0;
}


/**
 * @brief  APP_PackageData.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_PackageData(uint8_t DevID, uint8_t Type, uint8_t Targe, uint8_t Length, uint16_t *pData)
{
//	struct ringbuffer	*pFifo = CommPortTcb[COMM_P_0_TX].pFifo;
//	uint8_t	i;
//	uint8_t	index = 0;
//	uint8_t databuf[32] = {0};
//#if  USING_CRC16
//	uint16_t crc;
//#endif
//	
//	databuf[index++] = 0XA5;
//	databuf[index++] = 0X5A;
//	
//#if SEND_LENGTH
//	/* OFFSET_FRAME_LENGTH		8bit */
//	databuf[index++] = 1 +2 +(Length *2) +1;
//#else
//	databuf[index++] = 1 +2 +(Length *2);
//#endif	
//	/* OFFSET_DATA_TYPE			8bit */
//	databuf[index++] = Type;
//	/* OFFSET_DATA_TARGET		16bit */
////	databuf[index++] = (uint8_t)((Targe & 0xff00) >> 8);
////	databuf[index++] = (uint8_t)(Targe & 0x00ff);
//	databuf[index++] = DevID;
//	databuf[index++] = Targe;
//#if SEND_LENGTH	
//	/* OFFSET_DATA_LENGTH				8bit */
//	databuf[index++] = Length;
//#endif	
//	/* OFFSET_DATA_CONTENT_START 16bit */
//	for (i = 0; i < Length; i++)
//	{
//		databuf[index++] = (uint8_t)((pData[i] & 0xff00) >> 8);
//		databuf[index++] = (uint8_t)(pData[i] & 0x00ff);
//	}
//	
//#if  USING_CRC16
//	crc = IOT_CRC16_XMODEM(databuf+3,index-3);
//	databuf[2] += 2;
//	databuf[index++] = crc>>8;
//	databuf[index++] = crc&0xff;
//#endif
//		
//	ringbuffer_put_force(pFifo, databuf, index);

//	APP_StartTransmit(COMM_P_0_TX);
}

/**
 * @brief  APP_StartTransmit.
 * @note   None.
 * @param  PortIndex.
 * @retval None.
 */
void APP_StartTransmit(ENUM_DATA_COMM_PORT PortIndex)
{
//	struct ringbuffer	*pFifo;
//	uint16_t length;
//	UART_HandleTypeDef  *huart = CommPortTcb[PortIndex].huart;;
//	uint8_t  oncelength;
//	
//	if (huart->gState != HAL_UART_STATE_READY)
//		return;
//	
//	pFifo = CommPortTcb[PortIndex].pFifo;
//	length = ringbuffer_data_len(pFifo);
//		
//	if ( length )
//	{
//		if (length > ONCE_SAND_MAX)	
//			oncelength = ONCE_SAND_MAX;
//		else
//			oncelength = length;
//			
//		ringbuffer_get(pFifo, TxDataTemp, oncelength);
//			
//		HAL_UART_Transmit_DMA(huart, TxDataTemp, oncelength);
//	}
}
