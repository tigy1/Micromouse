/*
 * controller.h
 */

#ifndef INC_CONTROLLER_H_
#define INC_CONTROLLER_H_

#define PIVOT_TURN_GOAL 450 //amount of encoder counts for one wheel to turn 90 degrees x2
#define MOVE_DISTANCE_GOAL 620 //amount of encoder counts to move one cell

#include "main.h"

void move(int8_t n);
void pivot_turn(int8_t n);

#endif /* INC_CONTROLLER_H_ */
