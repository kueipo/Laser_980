/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Task/Task_Common.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define	USING_IAP
#if defined(USING_IAP)
	#define IAP_SIZE    	(20 * 1024)
	#define VECTOR_SIZE		(0xC0)
	void Remap_INT(void)
	{
	#if 0
		uint8_t i;
		uint32_t Data;
		uint32_t Address;
		for (i = 0; i < 48; i++)
		{
			Data =  *(__IO uint32_t*)(APP_ADDRESS + i * 4);
			Address = 0x20000000 + (i * 4);
			*(__IO uint32_t*)Address = (uint32_t)Data;
		}
	#else
		memcpy((void*)SRAM_BASE, (void*)(FLASH_BASE + IAP_SIZE), VECTOR_SIZE);
	#endif
		__HAL_SYSCFG_REMAPMEMORY_SRAM();
	}
#else
	#define Remap_INT(...)
#endif

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
static void Write_App_Flag(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	Remap_INT();
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
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_ADC_Init();
  MX_TIM14_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  
#if defined(ENABLE_FAL_SUPPORT)
	fal_init();
	#if defined(ENABLE_EL_SUPPORT)
		easyflash_init();
	#endif /* ENABLE_EL_SUPPORT */
#endif /* ENABLE_FAL_SUPPORT */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	Write_App_Flag();
		
//	printf("Ver %d.%d\r\n", BSP_VERSION / 10, BSP_VERSION % 10);
	
	BSP_Init();
	APP_Init();
	
	HAL_TIM_Base_Start_IT(&htim6);

	__HAL_TIM_CLEAR_IT(&htim14, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&htim14, TIM_IT_UPDATE);
		
  while (1)
  {
		Task_Pro_Handler_Callback();
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
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
static void Write_App_Flag(void)
{
	uint8_t flag;
#if defined(ENABLE_FAL_SUPPORT)
	const struct fal_partition *part = fal_partition_find ("upd");

	if (part == NULL)
		return;

	if (fal_partition_read(part, 0, &flag, 1) >= 0)
	{
		if (flag != ENTER_APP)
		{	
			flag = ENTER_APP;
			fal_partition_erase(part, 0, 1);
			fal_partition_write(part, 0, &flag, 1);
		}
	}
#else
	FLASH_Read(UPD_FLAG_ADDRESS, &flag, 1);
	if (flag != ENTER_APP)
	{
		flag = ENTER_APP;
		FLASH_Init();
		FLASH_Erase(UPD_FLAG_ADDRESS, 1);
		FLASH_Write(UPD_FLAG_ADDRESS, &flag, 1);
	}
#endif	
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
	Gol_log_err("Error_Handler\r\n");
	while (1);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	Gol_log_err("Wrong parameters value: file %s on line %d\r\n", file, line);
	while (1); 
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
