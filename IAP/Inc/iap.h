
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IAP_H
#define __IAP_H

/* Includes ------------------------------------------------------------------*/
#include "iap/inc/flash_if.h"
#include "iap/inc/ymodem.h"
#include "iap/inc/common.h"
#include "fal/inc/fal.h"
#include "string.h"
#include "main.h"

/* Exported define -----------------------------------------------------------*/
#define YMODEM_DOWNLOAD_PORT					(&huart2)

#ifndef APP_ADDRESS
	#define APP_ADDRESS						(FLASH_BASE + (20 * 1024))
#endif
#define DEV_TYPE							0x10 	/* Device types */
#define ENABLE_SERIAL_UPLOAD	0		 	/* default Disabled */
	#if ENABLE_SERIAL_UPLOAD
		#define FILE_NAME "bin"
	#endif /* ENABLE_SERIAL_UPLOAD */
#define ENABLE_MENU						0		 	/* default Disabled */
#define ENABLE_PRINT_DEBUG		0		 	/* Print debug message, default Disabled */
#define ENABLE_BOOT_MODE			0		 	/* enable boot mode, Modify as needed */

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

#endif  /* __IAP_H */
