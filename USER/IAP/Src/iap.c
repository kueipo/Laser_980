
/* Includes ------------------------------------------------------------------*/
#include "iap/INC/iap.h"

/* Global variables ----------------------------------------------------------*/
uint8_t aFileName[FILE_NAME_LENGTH];
const struct fal_partition *opt_area;
UART_HandleTypeDef *g_huart = YMODEM_DOWNLOAD_PORT;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static pFunction JumpToApplication;
static uint32_t JumpAddress;
#if ENABLE_MENU
static uint32_t FlashProtection = 0;
#endif /* ENABLE_MENU */
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Download a file via serial port
 * @param  None
 * @retval None
 */
COM_StatusTypeDef SerialDownload(void)
{
  g_huart = YMODEM_DOWNLOAD_PORT;
	
  uint32_t size = 0;
  COM_StatusTypeDef result;
	
#if ENABLE_BOOT_MODE
	Send_UpdataCMD(DEV_TYPE);

  HAL_UART_Receive(g_huart, aFileName, FILE_NAME_LENGTH, 1500);
  if (g_huart->RxXferCount != FILE_NAME_LENGTH)
  {
    return COM_ERROR;
  }
#endif
	
	/* Abort TX and RX */
  HAL_UART_Abort(g_huart);

  result = Ymodem_Receive(&size);

  return result;
}

/**
 * @brief  Upload a file via serial port.
 * @param  None
 * @retval None
 */
#if ENABLE_SERIAL_UPLOAD
#define SIZE_LENGTH 4
void SerialUpload(void)
{
  uint8_t status = 0;

  /* Read Size */
  uint32_t filesize = 0;
  uint32_t read_addr = 0;
  uint8_t buf[SIZE_LENGTH];

  uint8_t errors = 0;
  uint8_t times = 0;

#if ENABLE_PRINT_DEBUG /* Print debug message */
  Serial_PutString("\n\n\rSelect Receive File\n\r");
#endif /* ENABLE_PRINT_DEBUG */

  if (fal_partition_read(opt_area, read_addr, buf, SIZE_LENGTH) < SIZE_LENGTH)
    return;

  /* Calculate size */
  for (uint8_t i = 0; i < SIZE_LENGTH; i++)
  {
    filesize <<= 8;
    filesize += buf[i];
  }

  /* wait'C' */
  while (1)
  {
		HAL_UART_Receive(g_huart, &status, 1, RX_TIMEOUT);
    if (status == CRC16)
    {
			/* Continue for two 'C', enter Transmit mode */
      if (++times >= 2)
      {
        /* Transmit the flash image through ymodem protocol */
        status = Ymodem_Transmit((uint8_t *)(&read_addr), (const uint8_t *)FILE_NAME, filesize);
        //	status = Ymodem_Transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", USER_FLASH_SIZE);
        return;
      }
#if ENABLE_PRINT_DEBUG /* Print debug message */
			if (status != 0)
			{
			  Serial_PutString("\n\rError Occurred while Transmitting File\n\r");
			}
			else
			{
			  Serial_PutString("\n\rFile uploaded successfully \n\r");
			}
#endif /* ENABLE_PRINT_DEBUG */
    }
    else
    {
      times = 0;

      if (++errors >= (MAX_ERRORS))
        return;
    }
  }
}
#endif

/**
 * @brief  Display the Main Menu on HyperTerminal
 * @param  None
 * @retval None
 */
#if ENABLE_MENU
void IAP_Menu(void)
{
  g_huart = YMODEM_DOWNLOAD_PORT;
  uint8_t key = 0;

  Serial_PutString("\r\n======================================================================");
  Serial_PutString("\r\n=              (C) COPYRIGHT 2015 STMicroelectronics                 =");
  Serial_PutString("\r\n=                                                                    =");
  Serial_PutString("\r\n=  STM32F1xx In-Application Programming Application  (Version 1.0.0) =");
  Serial_PutString("\r\n=                                                                    =");
  Serial_PutString("\r\n=                                   By MCD Application Team          =");
  Serial_PutString("\r\n======================================================================");
  Serial_PutString("\r\n\r\n");

  /* Test if any sector of Flash memory where user application will be loaded is write protected */
  FlashProtection = FLASH_If_GetWriteProtectionStatus();

  while (1)
  {
    Serial_PutString("\r\n=================== Main Menu ============================\r\n\n");
    Serial_PutString("  Download image to the internal Flash ----------------- 1\r\n\n");
    Serial_PutString("  Upload image from the internal Flash ----------------- 2\r\n\n");
    Serial_PutString("  Execute the loaded application ----------------------- 3\r\n\n");

    if(FlashProtection != FLASHIF_PROTECTION_NONE)
    {
      Serial_PutString("  Disable the write protection ------------------------- 4\r\n\n");
    }
    else
    {
      Serial_PutString("  Enable the write protection -------------------------- 4\r\n\n");
    }
    Serial_PutString("==========================================================\r\n\n");

    /* Clean the input path */
//    __HAL_UART_FLUSH_DRREGISTER(DEV_UART_PORT);
	
    /* Receive key */
    HAL_UART_Receive(g_huart, &key, 1, RX_TIMEOUT);

    switch (key)
    {
    case '1' :
      /* Download user application in the Flash */
      SerialDownload();
		return;
   //   break;
    case '2' :
      /* Upload user application from the Flash */
      SerialUpload();
      break;
    case '3' :
      Serial_PutString("Start program execution......\r\n\n");
      /* execute the new program */
      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
      /* Jump to user application */
      JumpToApplication = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
      JumpToApplication();
      break;
    case '4' :
      if (FlashProtection != FLASHIF_PROTECTION_NONE)
      {
        /* Disable the write protection */
        if (FLASH_If_WriteProtectionConfig(FLASHIF_WRP_DISABLE) == FLASHIF_OK)
        {
          Serial_PutString("Write Protection disabled...\r\n");
          Serial_PutString("System will now restart...\r\n");
          /* Launch the option byte loading */
          HAL_FLASH_OB_Launch();
        }
        else
        {
          Serial_PutString("Error: Flash write un-protection failed...\r\n");
        }
      }
      else
      {
        if (FLASH_If_WriteProtectionConfig(FLASHIF_WRP_ENABLE) == FLASHIF_OK)
        {
          Serial_PutString("Write Protection enabled...\r\n");
          Serial_PutString("System will now restart...\r\n");
          /* Launch the option byte loading */
          HAL_FLASH_OB_Launch();
        }
        else
        {
          Serial_PutString("Error: Flash write protection failed...\r\n");
        }
      }
      break;
	default:
	Serial_PutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
	break;
    }
  }
}
#endif

void Execute_Application(void)
{
#if ENABLE_PRINT_DEBUG /* Print debug message */
  Serial_PutString("\r\nExecute the loaded application\r\n");
  HAL_Delay(500);
#endif /* ENABLE_PRINT_DEBUG */
	
  /* Judge whether the stack address value is between 0x 2000 0000 - 0x 2000 2000 */
  if (((*(__IO uint32_t *)APPLICATION_ADDRESS) & 0x2FFE0000) == 0x20000000)
  {
#if 0
		__disable_irq();
		/* Reset Peripheral Configuration */
		HAL_UART_MspDeInit(&huart1);
		HAL_UART_MspDeInit(&huart4);
		HAL_GPIO_DeInit(GPIOC,GPIO_PIN_12);
		HAL_GPIO_DeInit(GPIOB,GPIO_PIN_3);
		HAL_GPIO_DeInit(GPIOD,GPIO_PIN_2);
		
		HAL_DeInit();
		HAL_RCC_DeInit();
#endif
    /* Jump to user application */
		/* Corresponds to the second item in the app interrupt vector table, the reset address */
    JumpAddress = *(__IO uint32_t *)(APPLICATION_ADDRESS + 4); 																		
    /* Forcibly converting an address to a function pointer */
    JumpToApplication = (pFunction)JumpAddress;
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t *)APPLICATION_ADDRESS);
    /* Call the function (actually operate the app reset address to perform the reset operation) */
    JumpToApplication();
  }
  else
  {
#if ENABLE_PRINT_DEBUG /* Print debug message */
    Serial_PutString("\n\rAPPLICATION_ADDRESS error \n\r");
#endif /* ENABLE_PRINT_DEBUG */
		HAL_Delay(1000);
  }
}

/**
 * @brief  Execute_Updata
 * @param  None
 * @retval None
 */
void Execute_Updata(void)
{
}

/**
 * @brief  Send_UpdataCMD
 * @param  devtype
 * @retval None
 */
void Send_UpdataCMD(uint8_t devtype)
{
	aFileName[0] = 0xA5;
	aFileName[1] = 0x5A;
	aFileName[2] = 0x05;
	aFileName[3] = 0x82;
	aFileName[4] = devtype;
	aFileName[5] = 0xFC;
	aFileName[6] = 0x00;
	aFileName[7] = 0xAA;
	HAL_UART_Transmit(g_huart, aFileName, 8, TX_TIMEOUT);
}

/**
 * @brief  Send_DownloadCMD
 * @param  devtype
 * @retval None
 */
void Send_DownloadCMD(uint8_t devtype)
{
	aFileName[0] = 0xA5;
	aFileName[1] = 0x5A;
	aFileName[2] = 0x06;
	aFileName[3] = 0x83;
	aFileName[4] = devtype;
	aFileName[5] = 0xFC;
	aFileName[6] = 0x01;
	aFileName[7] = 0x00;
	aFileName[8] = 0xAA;
	HAL_UART_Transmit(g_huart, aFileName, 9, TX_TIMEOUT);
}
