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
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
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
		while (true);
	}

	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		mpu->dataReady = true;
	}

	/* ESP USART3 */

	void DMA1_Stream1_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(esp->Get_DMA_Rx_Handle());
	}

	void DMA1_Stream3_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(esp->Get_DMA_Tx_Handle());
	}

	void USART3_IRQHandler(void)
	{
		HAL_UART_IRQHandler(esp->Get_UART_Handle());
	}

	/*              */

	void DMA2_Stream2_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(&neo->hdma_usart1_rx);
	}

	void DMA1_Stream7_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(&logger->hdma_uart5_tx);
	}

	void UART5_IRQHandler(void)
	{
		HAL_UART_IRQHandler(&logger->huart);
	}

}
