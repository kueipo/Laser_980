#ifndef __APP_FACTORY_H
#define __APP_FACTORY_H

#ifdef __cplusplus
 extern "C" {
#endif

void APP_Factory_Init(void);
void APP_FactoryLaser(bool state);
bool APP_IsFactory(void);

#ifdef __cplusplus
}
#endif
  
#endif
