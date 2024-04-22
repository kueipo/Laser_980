#ifndef __APP_KEY_H
#define __APP_KEY_H

#ifdef __cplusplus
 extern "C" {
#endif
 
#define APP_KEY_PERIOD				1

typedef void (*KeyProcess)(uint8_t);

typedef struct 
{
#if 0
	uint32_t    ulTB;
	uint8_t     KeyId;
#endif
    uint16_t    usTime;			/* 按下计时 */
    uint8_t     ucState;		/* 按键状态 */
    uint16_t    usTS;			/* 松开计时 */
	uint8_t 	ucKeyDtcNum;	/* 点击次数 */
	uint16_t    usLongTH;		/* 长按计时阈值 */
	uint8_t		ucTrigger;		/* 按键触发 */
    KeyProcess  process;
}Key_Struct;


typedef enum
{
    KEY_PUSH     = 0,
    KEY_RELEASE,
    KEY_ERROR,
    
} ENUM_KEY_STATUS;
 
typedef enum
{
    KEY_PUSH_10MSBASE50MS  = 5,
	KEY_PUSH_10MSBASE100MS = 10,
	KEY_PUSH_10MSBASE200MS = 20,
	KEY_PUSH_10MSBASE250MS = 25,
	KEY_PUSH_10MSBASE350MS = 35,
    KEY_PUSH_10MSBASE1S    = 100,
	KEY_PUSH_10MSBASE2S	   = 200,
    KEY_PUSH_10MSBASE3S    = 300,
    KEY_PUSH_10MSBASE5S    = 500,
    
} ENUM_KEY_COUNT;

typedef enum
{
    NO_PRO = 0,
    SHOURT_PRO,  
    LONG_PRO,    
    DOUBLE_PRO,
	
} ENUM_KEY_TRIGGER;

void APP_KEY_TimeProc(uint16_t usPeriod);
void APP_KEY_Init(void);    
void APP_KEY_Task(void);
bool APP_KeyDelayConfig(uint8_t KeyId, bool bState);
uint8_t APP_ReadKeyVal(uint8_t KeyId);
bool APP_IsKeyPush(void);
#ifdef __cplusplus
}
#endif
  
   
#endif

