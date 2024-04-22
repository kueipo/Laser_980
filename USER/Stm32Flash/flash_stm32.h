
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_STM32_H
#define __FLASH_STM32_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Base address of the Flash sectors */

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */

/* Notable Flash addresses */
#define BSP_FLASH_SIZE  						64  //Flash size
//#define BSP_SRAM_SIZE   					8   //Sram size

/* Internal Flash memory size[Kbytes] <8-1024>, Default: 64 */
#define STM32_FLASH_START_ADRESS		FLASH_BASE
#define STM32_FLASH_SIZE            (BSP_FLASH_SIZE * 1024)

#define STM32_FLASH_END_ADDRESS     ((uint32_t)(STM32_FLASH_START_ADRESS + STM32_FLASH_SIZE))   //Flash end address

#define IAP_FLASH_SIZE							(20 * 1024)

#ifndef APP_ADDRESS
#define APP_ADDRESS									(STM32_FLASH_START_ADRESS + IAP_FLASH_SIZE)
#endif
#define UPD_FLAG_ADDRESS 				    (STM32_FLASH_END_ADDRESS - FLASH_PAGE_SIZE)

/* Internal SRAM memory size[Kbytes] <8-64>, Default: 8 */
#ifdef BSP_SRAM_SIZE
#define STM32_SRAM1_SIZE      		BSP_SRAM_SIZE                           //RAM size
#define STM32_SRAM1_END       		(SRAM_BASE + (STM32_SRAM1_SIZE * 1024)) //RAM end address
#endif /* BSP_SRAM_SIZE */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
int FLASH_Init(void);
int FLASH_Read(uint32_t addr, uint8_t *buf, size_t size);
int FLASH_Write(uint32_t addr, const uint8_t *buf, size_t size);
int FLASH_Erase(uint32_t addr, size_t size);

#endif  /* __FLASH_STM32_H */
