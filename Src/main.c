/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "fal/inc/fal.h"
#include "iap/inc/iap.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef CopyApp(uint8_t flag);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t flag;
#define NO_APP			
#define DOWN_TO_FAC		0xA0
#define DOWN_TO_DWN		0XAA
#define COPY_TO_DWN		0X55
#define COPY_TO_APP		0X5A
#define ENTER_APP			0XA5

static bool Write_App_Flag(uint8_t flag)
{
	uint32_t addr = 0 + IAP_FLAG_ADDR_SETOFF;
	opt_area = fal_partition_find ("upd");
	
	if (opt_area == NULL)
		return false;

	fal_partition_erase(opt_area, addr, 1);
	fal_partition_write(opt_area, addr, &flag, 1);
	return true;

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
	fal_init();
	
	opt_area = fal_partition_find("upd");

	if (fal_partition_read(opt_area, 0 + IAP_FLAG_ADDR_SETOFF, &flag, 1) >= 0)
	{
	//	flag = DOWN_TO_FAC;
		/* successful read data */
		switch (flag)
		{
		/* Lost APP, about to enter download mode */
		case 00:
		case 0xFF:
		case DOWN_TO_FAC:
			/* Download to default area */
			opt_area = fal_partition_find("fac");
			/* Download failed £¬ cpu reset*/
			if (SerialDownload() != COM_OK)
			{
				break;
			}
		/* Update from factory */
		default:
		case COPY_TO_DWN:
			Write_App_Flag(DOWN_TO_FAC);
			if (CopyApp(COPY_TO_DWN) == HAL_OK)
			{
				goto __copy_area;
			}
			break;
		case DOWN_TO_DWN:
			Write_App_Flag(COPY_TO_DWN);
			opt_area = fal_partition_find("dwn");
			/* Download failed */
			if (SerialDownload() != COM_OK)
			{
				break;
			}
__copy_area:
		/* Update from download */
		case COPY_TO_APP:	
			Write_App_Flag(COPY_TO_DWN);			
			if (CopyApp(COPY_TO_APP) != HAL_OK)
			{				
				break;
			}
		/* Enter the application */
		case ENTER_APP:
			Execute_Application();
			break;
		}
	}
	HAL_Delay(1000);
	HAL_FLASH_OB_Launch();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* RCC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(RCC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(RCC_IRQn);
}

/* USER CODE BEGIN 4 */
#define MAX_ERASE_SIZE	(4 * FLASH_PAGE_SIZE)
#define BUF_SIZE				(1 * 1024)

#define APP_ADDR_OFFSET 4
HAL_StatusTypeDef CopyApp(uint8_t flag)
{
  uint8_t buf[BUF_SIZE];
  uint32_t filesize = 0, size, erase_size;
  uint32_t read_addr = 0, write_addr = 0, erase_addr = write_addr;
  const struct fal_partition *destin;
  const struct fal_partition *source;
  int32_t res;

  /* Select Update Source */
  if (flag == COPY_TO_APP)
  {
    source = fal_partition_find("dwn");
    destin = fal_partition_find("app");
#if SUPPORT_MULTI_BIN
    read_addr = APP_ADDR_OFFSET;
#endif
  }
  /* Find Update Destinations */
  else
  {
    source = fal_partition_find("fac");
    destin = fal_partition_find("dwn");
  }
	
  /* Read Size */
  if (fal_partition_read(source, read_addr, buf, APP_ADDR_OFFSET) <= 0)
    return HAL_ERROR;

  /* Calculate size */
  for (uint8_t i = 0; i < 4; i++)
  {
    filesize <<= 8;
    filesize += buf[i];
  }

	/* Detection size */
	if (filesize == 0 || filesize >= destin->len)
		return HAL_ERROR;
	
	if (flag == COPY_TO_APP)
    read_addr += APP_ADDR_OFFSET;
	else
		filesize += APP_ADDR_OFFSET;
		
  for (; filesize > 0;)
  {
    /* Limit single maximum read/write */
    size = filesize;
    if (size > BUF_SIZE)
      size = BUF_SIZE;

    /* Read Data */
    if (fal_partition_read(source, read_addr, buf, size) != size)
      return HAL_ERROR;

    /* Check whether the erased space is enough to write data */
    if (erase_addr < (write_addr + size))
    {
      /* Calculate Unerased Space Size */
      erase_size = write_addr + filesize - erase_addr;
      if (erase_size > MAX_ERASE_SIZE)
        erase_size = MAX_ERASE_SIZE;

      res = fal_partition_erase(destin, erase_addr, erase_size);
      /* Erase successfully, record the location */
      if (res >= 0)
        erase_addr += res;
      else
        return HAL_ERROR;
    }

    /* Write Data */
    if (fal_partition_write(destin, write_addr, buf, size) != size)
      return HAL_ERROR;

    read_addr += size;
    write_addr += size;
    filesize -= size;
  }

  return HAL_OK;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
