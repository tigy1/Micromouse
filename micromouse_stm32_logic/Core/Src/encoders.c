/*
 * encoders.c
 */

#include "main.h"
#include "encoders.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim8;

/*
 * Implement this function so it returns the right encoder value
 */
int16_t getRightEncoderCounts() {
	return (int16_t) __HAL_TIM_GET_COUNTER(&htim8);
}

/*
 * Implement this function so it returns the left encoder value
 */
int16_t getLeftEncoderCounts() {
	return (int16_t) __HAL_TIM_GET_COUNTER(&htim3);
}

/*
 * This function has already been implemented for you. Enjoy! :)
 */
void resetEncoders() {
	TIM3->CNT = (uint16_t) 0;
	TIM8->CNT = (uint16_t) 0;
}
