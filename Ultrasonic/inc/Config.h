/*
 * Config.h
 *
 *  Created on: 10. 8. 2017
 *      Author: michp
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "HC_SR04.h"

namespace flyhero {

static const uint32_t US_TRIGG_PIN 			= GPIO_PIN_3;
static GPIO_TypeDef *const US_TRIGG_BASE 	= GPIOC;

static const uint32_t US_ECHO_PIN			= GPIO_PIN_2;
static GPIO_TypeDef *const US_ECHO_BASE		= GPIOC;

extern "C"
{
	void EXTI2_IRQHandler(void)
	{
		HAL_GPIO_EXTI_IRQHandler(US_ECHO_PIN);
	}

	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		HC_SR04::Instance().Update_State();
	}
}
}
#endif /* CONFIG_H_ */
