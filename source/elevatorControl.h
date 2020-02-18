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

typedef enum {
    ELEVATOR_GOING_UP,
    ELEVATOR_GOING_DOWN,
    ELEVATOR_STOPPED,
    ELEVATOR_OPERATING,
    ELEVATOR_STANDBY,
    ELEVATOR_OBSTRUCTED
} ElevatorState;

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
 * @brief Checks if the elevator has arrived at the wanted @p floor
 * @param floor The desired floor to check
 * @return 1 if at the desired @p floor, 0 otherwise.
*/
int elevatorArrivedAtFloor(int floor);

/**
 * @brief Commands the elevator to execute a given order. 
 * I.E move up to floor 3.
*/
void elevatorExecuteOrder();

/**
 * @brief The main loop that controls the elevator, polling everything.
*/
void elevatorMainLoop(void);


#endif