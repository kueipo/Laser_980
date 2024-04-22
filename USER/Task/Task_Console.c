
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Function prototypes -------------------------------------------------------*/
static void Main_Console(void);

#if defined(ENABLE_FAN_CONSOLE)
static void Fan_Console(void);
#endif /* ENABLE_FAN_CONSOLE */

/* Variables -----------------------------------------------------------------*/
typedef struct {	
	void (*TaskHook) (void);
} LocalTask_TypeDef;

static LocalTask_TypeDef TaskLocal[] = {
	{ *Main_Console		},
	
#if defined(ENABLE_FAN_CONSOLE)
	{ *Fan_Console		},
#endif /* ENABLE_FAN_CONSOLE */
	
};

volatile static uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/

#define TASK_TIMEOUT		100U		/* unit: ms */
/**
 * @brief  Main_Console.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Main_Console(void)
{
	uint32_t Tickstart = HAL_GetTick();
	uint8_t ch;
#if USING_CRC16
	uint16_t crc16 = 0;
#endif
	static uint8_t step = 0;
	static uint8_t Frame_Buf[16] = {0};
	static uint8_t index = 0;
	
	while ((RingBufferEmpty(g_stUartCfg[MAIN_CONSOLE_PORT].Rx_ring_buffer_p) == false) && 
				((HAL_GetTick() - Tickstart) < TASK_TIMEOUT))
	{
		/* Read data */		
		RingBufferGet(g_stUartCfg[MAIN_CONSOLE_PORT].Rx_ring_buffer_p, &ch, 1);
	
	#if 0	/* Echo */
		HAL_UART_Transmit(DEV_MAINUART_PORT, &ch, 1, 0xff);
	#endif
		
		switch (step)
		{
			case 0:
				if (FRAME_START_0 == ch)
					step++;
				break;
			case 1:
				if (FRAME_START_1 == ch)
					step++;
				else
					/* Failed to match frame header */
					step = 0;
				break;
			case 2:
				if (ch <= 0)
					/* Invalid data length */
					step = 0;
				else
				{
					Frame_Buf[index++] = ch;
					step++;
				}
				break;
			case 3:
				/* A frame of data has been read */
				if (index == Frame_Buf[OFFSET_FRAME_LENGTH])	
				{
					Frame_Buf[index] = ch;
					step = 0;
					index = 0;
					
				/* CRC verification */					
				#if USING_CRC16
					crc16 = (uint16_t)Frame_Buf[ Frame_Buf[OFFSET_FRAME_LENGTH] -1 ] << 8;
					crc16 += Frame_Buf[ Frame_Buf[OFFSET_FRAME_LENGTH] ] ;
					if (IOT_CRC16_XMODEM( (Frame_Buf+OFFSET_FRAME_LENGTH +1), Frame_Buf[OFFSET_FRAME_LENGTH] -2 ) != crc16 )
						break;
				#endif
					
					/* Processing data */
					App_Matching(Frame_Buf);
					return;
				}
				else
					Frame_Buf[index++] = ch;
		}
	}
}

#if defined(ENABLE_FAN_CONSOLE)
static void Fan_Console(void)
{
	uint32_t Tickstart = HAL_GetTick();
	uint8_t ch;
#if USING_CRC16
	uint16_t crc16 = 0;
#endif
	static uint8_t step = 0;
	static uint8_t Frame_Buf[16] = {0};
	static uint8_t index = 0;
	
	while ((RingBufferEmpty(g_stUartCfg[FAN_CONSOLE_PORT].Rx_ring_buffer_p) == false) && 
				((HAL_GetTick() - Tickstart) < TASK_TIMEOUT))
	{
		/* Read data */		
		RingBufferGet(g_stUartCfg[FAN_CONSOLE_PORT].Rx_ring_buffer_p, &ch, 1);
	
#if 0	/* Echo */
		HAL_UART_Transmit(DEV_MAINUART_PORT, &ch, 1, 0xff);
#endif
		
		switch (step)
		{
			case 0:
				if (FRAME_START_0 == ch)
					step++;
				break;
			case 1:
				if (FRAME_START_1 == ch)
					step++;
				else
					/* Failed to match frame header */
					step = 0;
				break;
			case 2:
				if (ch <= 0)
					/* Invalid data length */
					step = 0;
				else
				{
					Frame_Buf[index++] = ch;
					step++;
				}
				break;
			case 3:
				/* A frame of data has been read */
				if (index == Frame_Buf[OFFSET_FRAME_LENGTH])	
				{
					Frame_Buf[index] = ch;
					step = 0;
					index = 0;
					
				/* CRC verification */					
				#if USING_CRC16
					crc16 = (uint16_t)Frame_Buf[ Frame_Buf[OFFSET_FRAME_LENGTH] -1 ] << 8;
					crc16 += Frame_Buf[ Frame_Buf[OFFSET_FRAME_LENGTH] ] ;
					if (IOT_CRC16_XMODEM( (Frame_Buf+OFFSET_FRAME_LENGTH +1), Frame_Buf[OFFSET_FRAME_LENGTH] -2 ) != crc16 )
						break;
				#endif
					
					/* Processing data */
					Task_Fan_AppMatching(Frame_Buf);
					return;
				}
				else
					Frame_Buf[index++] = ch;
		}
	}
}
#endif

/**
 * @brief  Task_Console.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Console(void)
{
	for (uint8_t i = 0; i < TaskLocal_Total; i++)
	{
		TaskLocal[i].TaskHook();
	}
}
