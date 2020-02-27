/**
 * @file 
 * @brief Library with order and queue utilities
 * 
 */

#ifndef ORDER_H
#define ORDER_H
#include "hardware.h"
#include "elevatorControl.h"
#define NO_FLOOR -1

/**
 * @brief Polls the buttons and adds active buttons to lists.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */
void orderPoll(int *pQueue, Elevator *pElevator);

/**
 * @brief Adds active button to list.
 * 
 * @param floor The floor of the button.
 * 
 * @param orderType Type of the order.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */
void orderAdd(int floor, HardwareOrder orderType, int *pQueue, Elevator *pElevator);

/**
 * @brief Clears all orders at given @p floor.
 * 
 * @param floor The floor to be cleared of orders.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */
void orderClear(int floor, int *pQueue, Elevator *pElevator);

/**
 * @brief Clears all orders at all floors.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */
void orderClearAll(int *pQueue, Elevator *pElevator);

/**
 * @brief Is used in orderAdd to update the queue.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */
void orderAddToQueue(int *pQueue, Elevator *pElevator);

/**
 * @brief Removes the finished queue order and leftshifts once. Used in orderClear.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
 */ 
void orderShiftQueue(int *pQueue, Elevator *pElevator);

/**
 * @brief Shifts the queue back to make room for more urgent orders.
 * 
 * @param pQueue Pointer to queue.
 * 
 * @param pElevator Pointer to elevator.
*/
void orderShitfQueueBack(int *pQueue, Elevator *pElevator);

#endif