/**
 * @file
 * @brief This header contains most of the control utilities for the elevator.
 * 
*/

#ifndef ELEVATORCONTROL_H
#define ELEVATORCONTROL_H
#include "hardware.h"
#include "emergency.h"
#include "order.h"
#include "timerControl.h"

/**
 * @brief Polls the floor sensors and returns what floor the elevator is at.
 * 
 * @return Integer value of what floor the elevator is at, 0 if none.
*/
int elevatorPollFloor(void);


/**
 * @brief Moves elevator down until it reaches a known floor
 * 
 * @return Integer value of what floor the elevator is at.
*/
int elevatorToKnownState(void);

/**
 * @brief The main loop that controls the elevator, polling everything.
*/
void elevatorMainLoop(void);


#endif