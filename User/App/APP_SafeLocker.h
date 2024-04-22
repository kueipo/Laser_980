#ifndef __APP_SAFELOCKER_H
#define __APP_SAFELOCKER_H

typedef struct
{
	bool bState;
	bool bProtect;
} SafeLocker_Struct;

typedef enum
{
	SAFELOCKER_CONN = 0,
	SAFELOCKER_DISCONN,
	SAFELOCKER_ERROR,
} ENUM_SAFELOCKER_STATUS;

void APP_SafeLocker_Init(void);
void APP_SafeLocker_Task(void);
uint8_t APP_ReadSafeLockerConn(uint8_t id);
bool APP_WriteSafeLockerPROT(uint8_t id, bool bState);
bool APP_ReadSafeLockerPROT(uint8_t id);
bool APP_IsSafeLockErr(void);

#endif