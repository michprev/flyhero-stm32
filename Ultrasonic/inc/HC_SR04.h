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
	HC_SR04();
	HC_SR04(HC_SR04 const&);
	HC_SR04& operator=(HC_SR04 const&);

	enum echo_state { ECHO_HIGH, ECHO_LOW };

	bool running;
	echo_state state;
	uint32_t start_ticks;
	float distance;
public:
	static HC_SR04& Instance();

	void Init();
	void Update_State();
	void Start_Measurement();
	float Get_Distance();
};

} /* namespace flyhero */

#endif /* HC_SR04_H_ */
