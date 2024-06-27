#ifndef __APP_SAFELOCK_H
#define __APP_SAFELOCK_H

typedef struct
{
	bool bState;
	bool bProtect;
} SafeLock_Struct;

typedef enum
{
	SAFELOCK_CONN = 0,
	SAFELOCK_DISCONN,
	SAFELOCK_ERROR,
} ENUM_SAFELOCK_STATUS;

void APP_SafeLock_Init(void);
void APP_SafeLock_Task(void);
uint8_t APP_SafeLock_ReadConn(uint8_t id);
bool APP_SafeLock_WritePROT(uint8_t id, bool bState);
bool APP_SafeLock_ReadPROT(uint8_t id);
bool APP_SafeLock_IsErr(void);

#endif
