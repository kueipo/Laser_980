/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "APP_Common.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */
void DEV_UART_IRQHandler(UART_HandleTypeDef *huart);
void DEV_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart);
void BSP_UART_IRQHandler(UART_HandleTypeDef *huart);
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

  /* USER CODE END DMA1_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

  /* USER CODE END DMA1_Channel5_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	BSP_UART_IRQHandler(&huart1);
#if 0
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
#endif
  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	BSP_UART_IRQHandler(&huart2);
#if 0
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
#endif
  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */
	BSP_UART_IRQHandler(&huart4);
#if 0	
  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */
#endif
  /* USER CODE END UART4_IRQn 1 */
}

/**
  * @brief This function handles UART5 global interrupt.
  */
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */
	BSP_UART_IRQHandler(&huart5);
#if 0
  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */
#endif
  /* USER CODE END UART5_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt.
  */
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */

  /* USER CODE END TIM6_IRQn 1 */
}

/* USER CODE BEGIN 1 */
#include "DEV_Config.h"
#include "Task.h"
#include "Task_FeedBack.h"
#include "Task_PolityHigh.h"
#include "Task_DeviceDetection.h"
#include "Task/Task_Common.h"
extern void InsertNode(uint8_t index);

extern void APP_KEY_Task(void);
/**
* @brief  HAL_TIM_PeriodElapsedCallback.
* @note   None
* @param  htim TIM handle
* @retval None
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
{ 
	if (htim->Instance == TIM6) 
	{
		APP_TimeProc(10);
		Task_TimeProc(10);
	}
	
	else if (htim->Instance == TIM3)
	{
//		APP_Buzzer_Config(BUZZER_0, true);
	}
	
	if(TIM2 == htim->Instance)
	{
		BSP_Fan_CaptureOverflow();
  }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(TIM2 == htim->Instance)
	{
		BSP_Fan_Capture(htim);
	}
}

/**
  * @brief  PWM Pulse finished callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		if ( htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1 )
		{
			APP_LaserCountCallback();
			APP_Buzzer_Config(BUZZER_0, true);
		}
	}
}

#include "Task_Console.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
#if 0
	if(GPIO_Pin == FOOT_SWITCH_Pin)
	{
	}
#endif

#if 0
	if(GPIO_Pin == ENERGY_FB_Pin)
	{
	}
#endif

#if 0
	if(GPIO_Pin == SEED_SUPPLY_DETECTION_Pin)
	{
	}
#endif
}

/**
 * @brief  This function handles UART interrupt request.
 * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
 *                the configuration information for the specified UART module.
 * @retval None
 */
void BSP_UART_IRQHandler(UART_HandleTypeDef *huart)
{
	uint32_t isrflags = READ_REG(huart->Instance->SR);
	uint32_t cr1its = READ_REG(huart->Instance->CR1);
	uint32_t cr3its = READ_REG(huart->Instance->CR3);
	uint32_t errorflags = 0x00U;
	uint32_t dmarequest = 0x00U;

	uint8_t *buf;
	uint8_t size;

	/* If no error occurs */
	errorflags = (isrflags & (uint32_t)(USART_SR_PE | USART_SR_FE | USART_SR_ORE | USART_SR_NE));
	if (errorflags == RESET)
	{
		/* UART in mode Receiver -------------------------------------------------*/
		if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
		{
			BSP_UART_Receive(huart);
			return;
		}
	}

	/* If some errors occur */
	if ((errorflags != RESET) && (((cr3its & USART_CR3_EIE) != RESET) || ((cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET)))
	{
		/* UART parity error interrupt occurred ----------------------------------*/
		if (((isrflags & USART_SR_PE) != RESET) && ((cr1its & USART_CR1_PEIE) != RESET))
		{
			__HAL_UART_CLEAR_FEFLAG(huart);
		}

		/* UART noise error interrupt occurred -----------------------------------*/
		if (((isrflags & USART_SR_NE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
		{
			__HAL_UART_CLEAR_NEFLAG(huart);
		}

		/* UART frame error interrupt occurred -----------------------------------*/
		if (((isrflags & USART_SR_FE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
		{
			__HAL_UART_CLEAR_FEFLAG(huart);
		}

		/* UART Over-Run interrupt occurred --------------------------------------*/
		if (((isrflags & USART_SR_ORE) != RESET) && (((cr1its & USART_CR1_RXNEIE) != RESET) || ((cr3its & USART_CR3_EIE) != RESET)))
		{
#if 1
			huart->ErrorCode |= HAL_UART_ERROR_ORE;
#else
			__HAL_UART_CLEAR_OREFLAG(huart);
#endif
		}

		/* Call UART Error Call back function if need be --------------------------*/
		if (huart->ErrorCode != HAL_UART_ERROR_NONE)
		{
			/* UART in mode Receiver -----------------------------------------------*/
			if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
			{
				BSP_UART_Receive(huart);
			}
#if 1
			/* If Overrun error occurs, or if any error occurs in DMA mode reception,
				 consider error as blocking */
			dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR);
			if (((huart->ErrorCode & HAL_UART_ERROR_ORE) != RESET) || dmarequest)
			{
				__HAL_UART_CLEAR_OREFLAG(huart);

				/* Blocking error : transfer is aborted
				   Set the UART state ready to be able to start again the process,
				   Disable Rx Interrupts, and disable Rx DMA request, if ongoing */
				/* UART_EndRxTransfer BGEIN */

				/* Disable RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts */
				CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
				CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

				/* At end of Rx process, restore huart->RxState to Ready */
				huart->RxState = HAL_UART_STATE_READY;

				/* UART_EndRxTransfer END */
				
				/* Restart the UART DMA Rx request if enabled */
				if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
				{
					CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);
					
					buf = BSP_UART_GetBuff(huart);
					size = BSP_UART_GetBuffSize(huart);
					
					/* Abort the UART DMA Rx channel */
					if (huart->hdmarx != NULL)
					{
						HAL_DMA_Abort_IT(huart->hdmarx);
					}
					
					HAL_UART_Receive_DMA(huart, buf, size);
				}
				else
				{
					__HAL_UART_ENABLE_IT(huart, UART_IT_PE);
					__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);
					__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
				}
			}
			else
			{
				huart->ErrorCode = HAL_UART_ERROR_NONE;
			}
#endif
		}
		return;
	} /* End if some error occurs */

	/* Check current reception Mode :
	 If Reception till IDLE event has been selected : */
	if (((isrflags & USART_SR_IDLE) != 0U) && ((cr1its & USART_SR_IDLE) != 0U))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);

		/* Check if DMA mode is enabled in UART */
		if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
		{
			buf = BSP_UART_GetBuff(huart);
			size = BSP_UART_GetBuffSize(huart);
			
			/* Disable PE and ERR (Frame error, noise error, overrun error) interrupts */
			CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
			CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

			/* Disable the DMA transfer for the receiver request by resetting the DMAR bit
			  in the UART CR3 register */
			CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

			/* At end of Rx process, restore huart->RxState to Ready */
			huart->RxState = HAL_UART_STATE_READY;
					
			/* Last bytes received, so no need as the abort is immediate */
			(void)HAL_DMA_Abort(huart->hdmarx);
			
			/* receiving data */
			uint16_t nb_remaining_rx_data = (uint16_t)__HAL_DMA_GET_COUNTER(huart->hdmarx);
			if ((nb_remaining_rx_data > 0U) && (nb_remaining_rx_data < huart->RxXferSize))
			{
				BSP_UART_RxData(huart, buf, (huart->RxXferSize - nb_remaining_rx_data));
			}
			/* Start receiving data */
			HAL_UART_Receive_DMA(huart, buf, size);
			return;
		}
		else
		{
#if 0
			/* DMA mode not enabled */
			/* Check received length : If all expected data are received, do nothing.
			   Otherwise, if at least one data has already been received, IDLE event is to be notified to user */
			uint16_t nb_rx_data = huart->RxXferSize - huart->RxXferCount;
			if ((huart->RxXferCount > 0U) && (nb_rx_data > 0U))
			{
				/* Disable the UART Parity Error Interrupt and RXNE interrupts */
				CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));

				/* Disable the UART Error Interrupt: (Frame error, noise error, overrun error) */
				CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

				/* Rx process is completed, restore huart->RxState to Ready */
				huart->RxState = HAL_UART_STATE_READY;
				huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

				CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
				/*Call registered Rx complete callback*/
				huart->RxEventCallback(huart, nb_rx_data);
#else
				/*Call legacy weak Rx Event callback*/
				HAL_UARTEx_RxEventCallback(huart, nb_rx_data);
#endif
			}
#endif
			__HAL_UART_ENABLE_IT(huart, UART_IT_PE);
			__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);
			__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
			return;
		}
	}
	else
	{

	}
#if 1
	/* UART in mode Transmitter ------------------------------------------------*/
	if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
	{
		/* Check that a Tx process is ongoing */
		if (huart->gState == HAL_UART_STATE_BUSY_TX)
		{

			huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);

			if (--huart->TxXferCount == 0U)
			{
				/* Disable the UART Transmit Complete Interrupt */
				__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

				/* Enable the UART Transmit Complete Interrupt */
				__HAL_UART_ENABLE_IT(huart, UART_IT_TC);
			}
			return;
		}
		else
		{
			return;
		}
	}
#endif

	/* UART in mode Transmitter end --------------------------------------------*/
	if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		/* Disable the UART Transmit Complete Interrupt */
		__HAL_UART_DISABLE_IT(huart, UART_IT_TC);

		/* Tx process is ended, restore huart->gState to Ready */
		huart->gState = HAL_UART_STATE_READY;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
		/*Call registered Tx complete callback*/
		huart->TxCpltCallback(huart);
#else
		/*Call legacy weak Tx complete callback*/
		HAL_UART_TxCpltCallback(huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
		return;
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	BSP_UART_TxStart(huart);
}

/**
  * @brief  UART error callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
 	__HAL_UART_ENABLE_IT(huart, UART_IT_PE);
 	__HAL_UART_ENABLE_IT(huart, UART_IT_ERR);
 	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

/* USER CODE END 1 */
