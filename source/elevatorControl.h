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
    int stoppedBelow; /**Whether the elevator stopped below the current floor or not.*/
    ElevatorState state; /**The current state of the elevator.*/
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
 * @brief Checks if the elevator has arrived at the wanted @p floor , and 
 * stops it from moving if it has.
 * 
 * @param floor The desired floor to check if the elevator has arrived at.
 * 
 * @return 1 if at the desired @p floor , 0 otherwise.
*/
int elevatorArrivedAtFloor(int floor);

/**
 * @brief Commands the elevator to move in the direction it should.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */
void elevatorMovement(int* pQueue, Elevator* pElevator);

/**
 * @brief Commands the elevator to execute orders from the @p pQueue if 
 * the elevator was stopped or is in standby.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
*/
void elevatorExecuteOrder(int* pQueue, Elevator* pElevator);

/**
 * @brief Routine that checks if the elevator stops below the floor it was at.
 * 
 * @param pElevator Pointer to elevator.
*/
void elevatorCheckBelow(Elevator* pElevator);

/**
 * @brief The main loop that controls the elevator, polling everything.
 * 
 * @param pQueue pointer to queue.
 * @param pElevator pointer to elevator struct with info about the elevator.
*/
void elevatorMainLoop(int* pQueue, Elevator* pElevator);


#endif
