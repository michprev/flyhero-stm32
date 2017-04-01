#include "stm32f4xx_hal.h"
#include "main.h"

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(huart->Instance==USART3)
	{
		__USART3_CLK_ENABLE();
		__GPIOC_CLK_ENABLE();
		__DMA1_CLK_ENABLE();

		/**USART3 GPIO Configuration
		PC10     ------> USART3_TX
		PC11     ------> USART3_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* Peripheral DMA init*/

		DMA_HandleTypeDef *hdma_usart3_rx = esp->Get_DMA_Rx_Handle();

		hdma_usart3_rx->Instance = DMA1_Stream1;
		hdma_usart3_rx->Init.Channel = DMA_CHANNEL_4;
		hdma_usart3_rx->Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart3_rx->Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart3_rx->Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart3_rx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart3_rx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart3_rx->Init.Mode = DMA_CIRCULAR;
		hdma_usart3_rx->Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart3_rx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(hdma_usart3_rx) != HAL_OK)
		{
		}

		__HAL_LINKDMA(huart,hdmarx,*hdma_usart3_rx);

		DMA_HandleTypeDef *hdma_usart3_tx = esp->Get_DMA_Tx_Handle();

		hdma_usart3_tx->Instance = DMA1_Stream3;
		hdma_usart3_tx->Init.Channel = DMA_CHANNEL_4;
		hdma_usart3_tx->Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart3_tx->Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart3_tx->Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart3_tx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart3_tx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart3_tx->Init.Mode = DMA_NORMAL;
		hdma_usart3_tx->Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart3_tx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(hdma_usart3_tx) != HAL_OK)
		{
		}

		__HAL_LINKDMA(huart,hdmatx,*hdma_usart3_tx);

		HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
		HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
		HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==USART3)
	{
		__USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		PC10     ------> USART3_TX
		PC11     ------> USART3_RX
		*/

		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

		/* Peripheral DMA DeInit*/
		HAL_DMA_DeInit(huart->hdmarx);
		HAL_DMA_DeInit(huart->hdmatx);
	}
}
