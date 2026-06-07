/*
 * pid.c
 */

#include <stdlib.h>
#include "main.h"
#include "motors.h"
#include "encoders.h"
#include "pid.h"

#define GEAR_COUNTS 75.8
#define M_PI 3.14159265358979323846
#define WHEEL_DIAMETER 32
#define DISTANCE_TOL 15
#define ANGLE_TOL 5
#define CYCLE_GOAL 50
//UNITS ARE IN MM

uint8_t deriv_index = 0;
int16_t angle_history[DERIV_DELAY] = {0};

float kPw = 0.2; //angle
float kDw = 0.04;

float kPx = .1; //distance
float kDx = 0.01;

int16_t angle_diff = 0;
float distance_diff = 0;

int16_t old_angle_diff = 0;
float old_distance_diff = 0;

//updated by PID setters
static int16_t goal_distance = 0;
static int16_t goal_angle = 0;
static uint8_t goal_count = 0;

int32_t tester = 0;

void resetPID() {
	angle_diff = 0;
	old_angle_diff = 0;
	old_distance_diff = 0;

	resetMotors();
	resetEncoders();
	goal_distance = 0;
	goal_angle = 0;
	goal_count = 0;
}

//TODO:
// 1. Maybe add acceleration?

void updatePID() {
	//straight line
	int16_t encoder_R = getRightEncoderCounts();
	int16_t encoder_L = getLeftEncoderCounts();

	angle_diff = goal_angle - (encoder_L - encoder_R); //turning right is positive goal angle, left is negative goal angle
	old_angle_diff = angle_history[deriv_index];
	angle_history[deriv_index] = angle_diff;
	float angle_correction = kPw * angle_diff + kDw * (angle_diff - old_angle_diff); //right now just use P

	//limit pwm of angle to half (.4), limitPWM does it by .8
	if(angle_correction > 0.4){
		angle_correction = 0.4;
	} else if(angle_correction < -0.4){
		angle_correction = -0.4;
	}

	int16_t curr_distance = average(encoder_R, encoder_L);
	distance_diff = goal_distance - curr_distance;
	float distance_correction = kPx * distance_diff + kDx * (distance_diff - old_distance_diff);
	old_distance_diff = distance_diff;

	deriv_index++;
	if (deriv_index >= DERIV_DELAY){
		deriv_index = 0;
	}

	setMotorRPWM(distance_correction + angle_correction);
	setMotorLPWM(distance_correction - angle_correction);

	//goal check
	tester = abs(angle_diff);
	if (tester <= ANGLE_TOL && fabs(distance_diff) <= DISTANCE_TOL){
		if (goal_count < CYCLE_GOAL) {
			goal_count++;
		}
	} else{
		goal_count = 0;
	}

	//uint8_t distance = (uint8_t) ( (encoder_count/GEAR_COUNTS) * M_PI * WHEEL_DIAMETER);
}

void setPIDGoalD(int16_t distance) {
	//This function should set a variable that stores the goal distance
	goal_distance = distance;
}

void setPIDGoalA(int16_t angle) {
	//This function should set a variable that stores the goal angle
	goal_angle = angle;
}

int8_t PIDdone(void) { // There is no bool type in C. True/False values are represented as 1 or 0.
	//return true if rat reached goal for 50 systicks, else return false
	if (goal_count >= CYCLE_GOAL){
		return 1;
	} else{
		return 0;
	}
}

int16_t average(int16_t R, int16_t L){
	return (int16_t) (R + L)/2;
}
