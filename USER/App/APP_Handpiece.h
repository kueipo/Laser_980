#ifndef __APP_HANDPIECE_H
#define __APP_HANDPIECE_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct 
{
    bool	bState;
	bool	bProtect;
}Handpiece_Struct;


typedef enum
{
    HANDPIECE_CONN  = 0,
    HANDPIECE_DISCONN,
    HANDPIECE_ERROR,
} ENUM_HANDPIECE_STATUS;

void APP_Handpiece_Init(void);    
void APP_Handpiece_Task(void);
uint8_t APP_ReadHandpieceCONN(uint8_t HandpieceId);
void APP_WriteHandpiecePROT(uint8_t HandpieceId, bool bState);
bool APP_IsHandpieceError(void);

#ifdef __cplusplus
}
#endif
  
   
#endif
