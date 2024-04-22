
#include "Task/Task_Common.h"

//========================================================================
//                              	
//========================================================================
//void Task_SendData(void)
//{
//	uint16_t length = ringbuffer_data_len(pTxFifo_0);
//	uint8_t  oncelength = 0;
//	if ( length )
//	{
//		if (DEV_MAIN_PORT->gState == HAL_UART_STATE_READY)
//		{
//			if (length > ONCE_SAND_MAX)	
//			{
//				oncelength = ONCE_SAND_MAX;
//			}
//			else
//			{
//				oncelength = length;
//			}
//			
//			ringbuffer_get(pTxFifo_0, TxData, oncelength);
//			
//			if (HAL_UART_Transmit_DMA(DEV_MAIN_PORT, TxData, oncelength) != HAL_OK)
//			{
//				return;
//			}
//			if (oncelength == ONCE_SAND_MAX)
//			{
//				return;
//			}
//		}
//		else
//		{
//			return;
//		}
//	}
//	Task[TASK_SENDDATA].State = SUSPEND;
//}
