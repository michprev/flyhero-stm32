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

	/* MPU6050 data ready */


	void EXTI1_IRQHandler(void)
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
	}

	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		mpu->Data_Ready_Callback();
	}

	void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
		mpu->Data_Read_Callback();
	}

	void I2C1_EV_IRQHandler(void)
	{
		HAL_I2C_EV_IRQHandler(mpu->Get_I2C_Handle());
	}

	/* -- MPU6050 data ready -- */

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

	/* -- ESP USART3 -- */

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

	/* HAL TIM5 timer */

	void TIM5_IRQHandler(void)
	{
		TIM_HandleTypeDef *htim5 = Timer::Get_Handle();

		// Channel 2 for HAL 1 ms tick
		if (__HAL_TIM_GET_ITSTATUS(htim5, TIM_IT_CC2) == SET) {
			__HAL_TIM_CLEAR_IT(htim5, TIM_IT_CC2);
			uint32_t val = __HAL_TIM_GetCounter(htim5);
			//if ((val - prev) >= 1000) {
				HAL_IncTick();
				// Prepare next interrupt
				__HAL_TIM_SetCompare(htim5, TIM_CHANNEL_2, val + 1000);
				//prev = val;
			//}
			//else {
			//	printf("should not happen\n");
			//}
		}
		//HAL_TIM_IRQHandler(Timer::Get_Handle());
	}

	/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
		if (htim->Instance == TIM5) {
			HAL_IncTick();
		}
	}*/

	/* -- HAL TIM5 timer --  */

}
