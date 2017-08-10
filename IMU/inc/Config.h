/*
 * Config.h
 *
 *  Created on: 9. 8. 2017
 *      Author: michp
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stm32f4xx_hal.h>
#include "MPU6050.h"

namespace flyhero {

static I2C_TypeDef *const IMU_I2C 			= I2C1;
// SCL
static const uint32_t IMU_SCL_PIN 			= GPIO_PIN_8;
static GPIO_TypeDef *const IMU_SCL_BASE 	= GPIOB;
// SDA
static const uint32_t IMU_SDA_PIN 			= GPIO_PIN_9;
static GPIO_TypeDef *const IMU_SDA_BASE 	= GPIOB;

// DMA
static DMA_Stream_TypeDef *const IMU_DMA 	= DMA1_Stream5;
static const uint32_t IMU_DMA_CHANNEL		= DMA_CHANNEL_1;

// INT
static GPIO_TypeDef *const IMU_INT_BASE		= GPIOB;
static const uint32_t IMU_INT_PIN			= GPIO_PIN_1;

// we also need to implement IRQs here
extern "C" {
	void DMA1_Stream5_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(MPU6050::Instance().Get_DMA_Rx_Handle());
	}

	void EXTI1_IRQHandler(void)
	{
		HAL_GPIO_EXTI_IRQHandler(IMU_INT_PIN);
	}

	void I2C1_EV_IRQHandler(void)
	{
		HAL_I2C_EV_IRQHandler(MPU6050::Instance().Get_I2C_Handle());
	}

	void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
		if (MPU6050::Instance().Data_Read_Callback != NULL)
			MPU6050::Instance().Data_Read_Callback();
	}

	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		if (MPU6050::Instance().Data_Ready_Callback != NULL)
			MPU6050::Instance().Data_Ready_Callback();
	}
}

}

#endif /* CONFIG_H_ */
