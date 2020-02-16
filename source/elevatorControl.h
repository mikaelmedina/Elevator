/**
 * @file
 * @brief This header contains most of the control utilities for the elevator.
 * 
*/

#ifndef ELEVATORCONTROL_H
#define ELEVATORCONTROL_H
#include "hardware.h"

/**
 * @brief Polls the floor sensors and returns what floor the elevator is at.
 * 
 * @return Integer value of what floor the elevator is at, 0 if none.
*/
int elevatorPollFloor(void);



#endif