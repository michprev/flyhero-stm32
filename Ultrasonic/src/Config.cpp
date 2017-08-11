/*
 * Config.cpp
 *
 *  Created on: 12. 8. 2017
 *      Author: michp
 */

#include <Config.h>

namespace flyhero {

HC_SR04 US1(GPIO_PIN_3, GPIOC, GPIO_PIN_2, GPIOC);
HC_SR04 US2(GPIO_PIN_3, GPIOB, GPIO_PIN_5, GPIOB);

extern "C"
{
	void EXTI2_IRQHandler(void) {
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
	}

	void EXTI9_5_IRQHandler(void) {
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	}

	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
		switch (GPIO_Pin) {
		case GPIO_PIN_2:
			US1.Update_State();
			break;
		case GPIO_PIN_5:
			US2.Update_State();
			break;
		}
	}
}

}
