/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "HC_SR04.h"
#include "Timer.h"
#include "Config.h"

using namespace flyhero;

extern "C" void initialise_monitor_handles(void);

int main(void)
{
	HAL_Init();
	initialise_monitor_handles();

	US1.Init();

	while (true) {
		US1.Start_Measurement();

		Timer::Delay_ms(500);

		printf("%f cm\n", US1.Get_Distance());
	}
}
