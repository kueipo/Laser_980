
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IAP_H
#define __IAP_H

/* Includes ------------------------------------------------------------------*/
#include "iap/inc/flash_if.h"
#include "iap/inc/ymodem.h"
#include "iap/inc/common.h"
#include "fal/inc/fal.h"
#include "string.h"
#include "usart.h"
#include "Stm32Flash/flash_stm32.h"

/* Exported define -----------------------------------------------------------*/
#define YMODEM_DOWNLOAD_PORT	(&huart2)
//#define YMODEM_UPLOAD_PORT		(&huart2)

//#if SUPPORT_MULTI_BIN

#ifndef APP_ADDRESS
	#define APP_ADDRESS					(FLASH_BASE + (20 * 1024))
#endif

#define DEV_TYPE							0x60 	/* Device types */

#define ENABLE_SERIAL_UPLOAD	0		 	/* default Disabled */
	#if ENABLE_SERIAL_UPLOAD
		#define FILE_NAME 				"bin"
	#endif /* ENABLE_SERIAL_UPLOAD */
	
#define ENABLE_MENU						0		 	/* default Disabled */
#define ENABLE_PRINT_DEBUG		0		 	/* Print debug message, default Disabled */
#define ENABLE_BOOT_MODE			1		 	/* enable boot mode, Modify as needed */

#define ENABLE_FAL_SUPPORT		1			/* enable FAL Driver Component */

/* Exported variables --------------------------------------------------------*/
typedef  void (*pFunction)(void);
extern uint8_t aFileName[FILE_NAME_LENGTH];
extern const struct fal_partition *opt_area;
extern UART_HandleTypeDef *g_huart;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void IAP_Menu(void);
void Execute_Application(void);
void Execute_Updata(void);
COM_StatusTypeDef SerialDownload(void);
void SerialUpload(void);
void Send_UpdataCMD(uint8_t devtype);
void Send_DownloadCMD(uint8_t devtype);

#endif  /* __IAP_H */
