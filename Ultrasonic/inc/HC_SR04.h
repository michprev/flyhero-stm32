/*
 * HC_SR04.h
 *
 *  Created on: 10. 8. 2017
 *      Author: michp
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_

#include <stm32f4xx_hal.h>
#include "Timer.h"

namespace flyhero {

class HC_SR04 {
private:
	enum echo_state { ECHO_HIGH, ECHO_LOW };

	const uint32_t TRIGG_PIN;
	GPIO_TypeDef *const TRIGG_BASE;
	const uint32_t ECHO_PIN;
	GPIO_TypeDef *const ECHO_BASE;

	bool running;
	echo_state state;
	uint32_t start_ticks;
	float distance;
public:
	HC_SR04(uint32_t trigg_pin, GPIO_TypeDef *const trigg_base,
			uint32_t echo_pin, GPIO_TypeDef *const echo_base);

	void Init();
	void Update_State();
	void Start_Measurement();
	float Get_Distance();
};

} /* namespace flyhero */

#endif /* HC_SR04_H_ */
