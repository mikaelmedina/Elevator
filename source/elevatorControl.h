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

/* Brukes i orderAddToQueue, update hvis bedre løsning finnes. Må muligens legges til i c-fila. */
typedef struct Elevator{
    int currentFloor;
    int nextFloor;
    ElevatorState state;
} Elevator;


/**
 * @brief Polls the floor sensors and returns what floor the elevator is at.
 * 
 * @return Integer value of what floor the elevator is at, -1 if none.
*/
int elevatorPollFloor(void);


/**
 * @brief Moves elevator down until it reaches a known floor
 * 
 * @return Integer value of what floor the elevator is at.
*/
int elevatorToKnownState(Elevator* pElevator);

/**
 * @brief This function handles every function that needs to be called
 * when elevator arrives at the give @p floor.
 * 
 * @param floor Floor the elevator has arrived at.
 * @param pQueue pointer to queue.
 * @param pElevator pointer to elevator struct with info about the elevator.
*/
void elevatorArrival(int floor, int* pQueue, Elevator* pElevator);

/**
 * @brief Checks if the elevator has arrived at the wanted @p floor, and 
 * stops it from moving if it has.
 * @param floor The desired floor to check if the elevator has arrived at.
 * @return 1 if at the desired @p floor, 0 otherwise.
*/
int elevatorArrivedAtFloor(int floor);

/**
 *
 */
void elevatorMovement(Elevator* pElevator);

/**
 * @brief Commands the elevator to execute a given order. 
 * I.E move up to floor 3.
*/
void elevatorExecuteOrder(int* pQueue, Elevator* pElevator);

/**
 * @brief The main loop that controls the elevator, polling everything.
 * 
 * @param pQueue pointer to queue.
 * @param pElevator pointer to elevator struct with info about the elevator.
*/
void elevatorMainLoop(int* pQueue, Elevator* pElevator);


#endif