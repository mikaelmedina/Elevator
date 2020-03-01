/**
 * @file
 * @brief This header contains most of the control utilities for the elevator.
 * 
*/

#ifndef ELEVATORCONTROL_H
#define ELEVATORCONTROL_H
#include "hardware.h"

/**
 * @brief Different states for the elevator.
*/
typedef enum {
    ELEVATOR_GOING_UP,
    ELEVATOR_GOING_DOWN,
    ELEVATOR_STOPPED,
    ELEVATOR_STANDBY,
} ElevatorState;

/**
 * @brief Struct that holds information about an elevator.
*/
typedef struct Elevator{
    int currentFloor; /**The last floor the elevator stopped at/passed.*/
    int nextFloor; /**The next floor the elevator is going to.*/
    ElevatorState state; /**The current state of the elevator.*/
    ElevatorState lastFloorState; /**State elevator entered last time it left/passed a floor.*/
} Elevator;

#include "emergency.h"
#include "order.h"
#include "timerControl.h"


/**
 * @brief Polls the floor sensors and returns what floor the elevator is at.
 * 
 * @return Integer value of what floor the elevator is at, -1 if none.
*/
int elevatorPollFloor(void);


/**
 * @brief Moves elevator down until it reaches a known floor.
 * 
 * @return Integer value of what floor the elevator is at.
*/
int elevatorToKnownState(Elevator* pElevator);

/**
 * @brief This function handles every function that needs to be called
 * when elevator arrives at the given @p floor .
 * 
 * @param floor Floor the elevator has arrived at.
 * @param pQueue Pointer to queue.
 * @param pElevator Pointer to elevator struct with info about the elevator.
*/
void elevatorArrival(int floor, int* pQueue, Elevator* pElevator);

/**
 * @brief The main loop that controls the elevator, polling everything.
 * 
 * @param pQueue pointer to queue.
 * @param pElevator pointer to elevator struct with info about the elevator.
*/
void elevatorMainLoop(int* pQueue, Elevator* pElevator);


#endif
