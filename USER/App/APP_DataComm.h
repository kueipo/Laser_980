#ifndef __APP_DATACOMM_H
#define __APP_DATACOMM_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum
{
    COMM_P_0_TX = 0x00,
    COMM_P_0_RX,
	
	COMM_PORT_MAX,
}ENUM_DATA_COMM_PORT;

typedef struct 
{
	struct ringbuffer	*pFifo;
	UART_HandleTypeDef  *huart;
} DataComm_Struct;

void APP_DataComm_Init(void);
uint16_t APP_WriteData(ENUM_DATA_COMM_PORT PortIndex, const uint8_t *ptr, uint16_t length);
uint16_t APP_ReadData(ENUM_DATA_COMM_PORT PortIndex, uint8_t *ptr, uint16_t length);
void APP_PackageData(uint8_t DevID, uint8_t Type, uint8_t Targe, uint8_t Length, uint16_t *pData);
void APP_StartTransmit(ENUM_DATA_COMM_PORT PortIndex);

#ifdef __cplusplus
}
#endif
#endif
