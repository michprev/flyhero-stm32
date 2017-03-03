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
extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

extern "C" void HardFault_Handler(void)
{
	while (true);
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	mpu->dataReady = true;
}

extern "C" void DMA1_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&esp8266->hdma_usart3_tx);
}

extern "C" void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&esp8266->huart);
}

extern "C" void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&neo->hdma_usart1_rx);
}

extern "C" void DMA1_Stream7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&logger->hdma_uart5_tx);
}

extern "C" void UART5_IRQHandler(void)
{
	HAL_UART_IRQHandler(&logger->huart);
}
