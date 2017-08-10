/*
 * HC_SR04.cpp
 *
 *  Created on: 10. 8. 2017
 *      Author: michp
 */

#include <HC_SR04.h>
#include "Config.h"

namespace flyhero {

HC_SR04& HC_SR04::Instance() {
	static HC_SR04 instance;

	return instance;
}

HC_SR04::HC_SR04() {
	this->running = false;
	this->state = ECHO_LOW;
	this->start_ticks = 0;
	this->distance = 0;
}

void HC_SR04::Init() {
	// enable TRIGG GPIO base clock
	switch ((uint32_t)US_TRIGG_BASE) {
	case GPIOA_BASE:
		if (__GPIOA_IS_CLK_DISABLED())
			__GPIOA_CLK_ENABLE();
		break;
	case GPIOB_BASE:
		if (__GPIOB_IS_CLK_DISABLED())
			__GPIOB_CLK_ENABLE();
		break;
	case GPIOC_BASE:
		if (__GPIOC_IS_CLK_DISABLED())
			__GPIOC_CLK_ENABLE();
		break;
	case GPIOD_BASE:
		if (__GPIOD_IS_CLK_DISABLED())
			__GPIOD_CLK_ENABLE();
		break;
	case GPIOE_BASE:
		if (__GPIOE_IS_CLK_DISABLED())
			__GPIOE_CLK_ENABLE();
		break;
	case GPIOF_BASE:
		if (__GPIOF_IS_CLK_DISABLED())
			__GPIOF_CLK_ENABLE();
		break;
	case GPIOG_BASE:
		if (__GPIOG_IS_CLK_DISABLED())
			__GPIOG_CLK_ENABLE();
		break;
	case GPIOH_BASE:
		if (__GPIOH_IS_CLK_DISABLED())
			__GPIOH_CLK_ENABLE();
		break;
	}

	// enable ECHO GPIO base clock
	switch ((uint32_t)US_ECHO_BASE) {
	case GPIOA_BASE:
		if (__GPIOA_IS_CLK_DISABLED())
			__GPIOA_CLK_ENABLE();
		break;
	case GPIOB_BASE:
		if (__GPIOB_IS_CLK_DISABLED())
			__GPIOB_CLK_ENABLE();
		break;
	case GPIOC_BASE:
		if (__GPIOC_IS_CLK_DISABLED())
			__GPIOC_CLK_ENABLE();
		break;
	case GPIOD_BASE:
		if (__GPIOD_IS_CLK_DISABLED())
			__GPIOD_CLK_ENABLE();
		break;
	case GPIOE_BASE:
		if (__GPIOE_IS_CLK_DISABLED())
			__GPIOE_CLK_ENABLE();
		break;
	case GPIOF_BASE:
		if (__GPIOF_IS_CLK_DISABLED())
			__GPIOF_CLK_ENABLE();
		break;
	case GPIOG_BASE:
		if (__GPIOG_IS_CLK_DISABLED())
			__GPIOG_CLK_ENABLE();
		break;
	case GPIOH_BASE:
		if (__GPIOH_IS_CLK_DISABLED())
			__GPIOH_CLK_ENABLE();
		break;
	}

	GPIO_InitTypeDef trigg;
	trigg.Pin = US_TRIGG_PIN;
	trigg.Mode = GPIO_MODE_OUTPUT_PP;
	trigg.Speed = GPIO_SPEED_HIGH;
	trigg.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(US_TRIGG_BASE, &trigg);

	HAL_GPIO_WritePin(US_TRIGG_BASE, US_TRIGG_PIN, GPIO_PIN_RESET);

	GPIO_InitTypeDef echo;
	echo.Pin = US_ECHO_PIN;
	echo.Mode = GPIO_MODE_IT_RISING_FALLING;
	echo.Speed = GPIO_SPEED_HIGH;
	echo.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(US_ECHO_BASE, &echo);

	switch (US_ECHO_PIN) {
	case GPIO_PIN_0:
		HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		break;
	case GPIO_PIN_1:
		HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);
		break;
	case GPIO_PIN_2:
		HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI2_IRQn);
		break;
	case GPIO_PIN_3:
		HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI3_IRQn);
		break;
	case GPIO_PIN_4:
		HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI4_IRQn);
		break;
	case GPIO_PIN_5:
	case GPIO_PIN_6:
	case GPIO_PIN_7:
	case GPIO_PIN_8:
	case GPIO_PIN_9:
		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		break;
	case GPIO_PIN_10:
	case GPIO_PIN_11:
	case GPIO_PIN_12:
	case GPIO_PIN_13:
	case GPIO_PIN_14:
	case GPIO_PIN_15:
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
		break;
	}
}

void HC_SR04::Update_State() {
	if (!this->running)
		return;

	if (this->state == ECHO_LOW) {
		this->start_ticks = Timer::Get_Tick_Count();

		this->state = ECHO_HIGH;
	}
	else {
		uint32_t dt = Timer::Get_Tick_Count() - this->start_ticks;
		this->distance = dt * 0.0001f * 331.57f * 0.5f; // in cm

		this->state = ECHO_LOW;
	}
}

void HC_SR04::Start_Measurement() {
	HAL_GPIO_WritePin(US_TRIGG_BASE, US_TRIGG_PIN, GPIO_PIN_SET);
	Timer::Delay_us(10);
	HAL_GPIO_WritePin(US_TRIGG_BASE, US_TRIGG_PIN, GPIO_PIN_RESET);
}

float HC_SR04::Get_Distance() {
	return this->distance;
}

} /* namespace flyhero */
