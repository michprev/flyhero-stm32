/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */



extern "C" {

	void SysTick_Handler(void)
	{
		HAL_IncTick();
		HAL_SYSTICK_IRQHandler();
	}

	void HardFault_Handler(void)
	{
		printf("hard fault\n");
	}

	void DMA1_Stream1_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(esp->Get_DMA_Rx_Handle());
	}

	/*void DMA1_Stream3_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(esp->Get_DMA_Tx_Handle());
	}

	void USART3_IRQHandler(void)
	{
		HAL_UART_IRQHandler(esp->Get_UART_Handle());
	}*/

}

