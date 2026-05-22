/*
 * pid.c
 */

#include "main.h"
#include "motors.h"
#include "encoders.h"

#define GEAR_COUNTS 75.8
#define M_PI 3.14159265358979323846
#define WHEEL_DIAMETER 32
//UNITS ARE IN MM

float kPw = .1; //angle
float kDw = 1;

float kPx = 1; //distance
float kDx = 1;

int16_t old_angle_diff = 0;

//updated by PID setters
int goal_distance = 0;
int goal_angle = 0;

void resetPID() {
	/*
	 * For assignment 3.1: This function does not need to do anything
	 * For assignment 3.2: This function should reset all the variables you define in this file to help with PID to their default
	 *  values. You should also reset your motors and encoder counts (if you tell your rat to turn 90 degrees, there will be a big
	 * difference in encoder counts after it turns. If you follow that by telling your rat to drive straight without first
	 * resetting the encoder counts, your rat is going to see a huge angle error and be very unhappy).
	 *
	 * You should additionally set your distance and error goal values (and your oldDistanceError and oldAngleError) to zero.
	 */

}

void updatePID() {
	/*
	 * This function will do the heavy lifting PID logic. It should do the following: read the encoder counts to determine an error,
	 * use that error along with some PD constants you determine in order to determine how to set the motor speeds, and then actually
	 * set the motor speeds.
	 *
	 * For assignment 3.1: implement this function to get your rat to drive forwards indefinitely in a straight line. Refer to pseudocode
	 * example document on the google drive for some pointers
	 *
	 * TIPS (assignment 3.1): Create kPw and kDw variables, use a variable to store the previous error for use in computing your
	 * derivative term. You may get better performance by having your kDw term average the previous handful of error values instead of the
	 * immediately previous one, or using a stored error from 10-15 cycles ago (stored in an array?). This is because systick calls so frequently
	 * that the error change may be very small and hard to operate on.
	 *
	 * For assignment 3.2: implement this function so it calculates distanceError as the difference between your goal distance and the average of
	 * your left and right encoder counts. Calculate angleError as the difference between your goal angle and the difference between your left and
	 * right encoder counts. Refer to pseudocode example document on the google drive for some pointers.
	 */

	//straight line
	int16_t encoder_R = getRightEncoderCounts();
	int16_t encoder_L = getLeftEncoderCounts();
	int16_t angle_diff = encoder_R - encoder_L;
	float angle_correction = kPw * angle_diff + kDw * (angle_diff - old_angle_diff); //right now just use P
	old_angle_diff = angle_diff;

	float distance_diff = 0.4;
	float distance_correction = kPx * distance_diff;

	setMotorRPWM(distance_correction - angle_correction);
	setMotorLPWM(distance_correction + angle_correction);

	//uint8_t distance = (uint8_t) ( (encoder_count/GEAR_COUNTS) * M_PI * WHEEL_DIAMETER);
}

void setPIDGoalD(int16_t distance) {
	//This function should set a variable that stores the goal distance.
	goal_distance = distance;
}

void setPIDGoalA(int16_t angle) {
	/*
	 * For assignment 3.1: this function does not need to do anything
	 * For assignment 3.2: This function should set a variable that stores the goal angle.
	 */
}

int8_t PIDdone(void) { // There is no bool type in C. True/False values are represented as 1 or 0.
	/*
	 * For assignment 3.1: this function does not need to do anything (your rat should just drive straight indefinitely)
	 * For assignment 3.2:This function should return true if the rat has achieved the set goal. One way to do this by having updatePID() set some variable when
	 * the error is zero (realistically, have it set the variable when the error is close to zero, not just exactly zero). You will have better results if you make
	 * PIDdone() return true only if the error has been sufficiently close to zero for a certain number, say, 50, of SysTick calls in a row.
	 */

	return 1;
}
