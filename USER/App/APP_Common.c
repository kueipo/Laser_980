
#include "APP/APP_Common.h"

/*****************************************************************************
Function name : APP_Init
Description: APP层的初始化函数，在程序上电初始化的时候调用。	 
Input: NONE		
Return: NONE     
Notes:
******************************************************************************/
void APP_Init(void)
{
//	APP_Voltage_Init();
//	APP_Handpiece_Init();
//  APP_KEY_Init();
//	APP_Pump_Init();
//	APP_Cooler_Init();
//	APP_Water_Init();
//	APP_SafeLocker_Init();
//	APP_LED_Init();
//	APP_Laser_Init();
//	APP_Factory_Init();
//	APP_Mos_Init();
//	APP_DataComm_Init();
//	APP_Motor_Init();
//	APP_DC24V_Init();
	APP_Laser_Init();
}

/*****************************************************************************
Function name : APP_TimeProc
Description: APP层 系统时基定时器回调函数，在定时器中被调用，建议1ms执行一次。
Input: usPeriod->函数被调用的周期（ms）
Return: NONE     
Notes:
******************************************************************************/
void APP_TimeProc(uint32_t usPeriod)
{
	/***********APP KEY时基************/
	//	APP_KEY_TimeProc(1);
	/***********APP LED时基************/
	//	APP_LED_TimeProc(1);
}


bool Send_Data(uint8_t DevID, uint8_t Type, uint8_t Targe, uint8_t Length, uint16_t *pData)
{
	uint8_t	i;
	uint8_t	index = 0;
	uint8_t databuf[32] = {0};
#if  USING_CRC16
	uint16_t crc;
#endif
	
	databuf[index++] = 0XA5;
	databuf[index++] = 0X5A;

	if (INDEX_TYPE_OPERATE == Type)
		databuf[index++] = 1 +2 +(Length *2) +1;
	else
		databuf[index++] = 1 +2 +(Length *2);
	
	/* OFFSET_DATA_TYPE			8bit */
	databuf[index++] = Type;
	/* OFFSET_DATA_TARGET		16bit */
	databuf[index++] = DevID;
	databuf[index++] = Targe;
	
#if SEND_LENGTH	
	/* OFFSET_DATA_LENGTH				8bit */
	databuf[index++] = Length;
#endif
	
	if (INDEX_TYPE_OPERATE == Type)
		databuf[index++] = Length;
		
	/* OFFSET_DATA_CONTENT_START 16bit */
	for (i = 0; i < Length; i++)
	{
		databuf[index++] = (uint8_t)((pData[i] & 0xff00) >> 8);
		databuf[index++] = (uint8_t)(pData[i] & 0x00ff);
	}
	
#if  USING_CRC16
	crc = IOT_CRC16_XMODEM(databuf +3,index -3);
	databuf[2] += 2;
	databuf[index++] = crc >> 8;
	databuf[index++] = crc & 0xff;
#endif
		
	uint8_t uartid;
	switch(DevID)
	{
		case DEVICE_TYPE:
			uartid = MAIN_CONSOLE_PORT;
			break;
		
#if defined(FAN_CONSOLE_PORT)
		case DEV_INDEX_FAN:
			uartid = FAN_CONSOLE_PORT;
			break;
#endif /* FAN_CONSOLE_PORT */
		
#if defined(PROT_CONSOLE_PORT)
		case DEV_INDEX_PORTECT:
			uartid = PROT_CONSOLE_PORT;
			break;
#endif /* PROT_CONSOLE_PORT */
		
		default:
			return false;
	}
	BSP_UART_TxDataToID(uartid, (uint8_t *)databuf, index);
	
	return true;
}
