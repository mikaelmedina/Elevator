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
 */
void orderPoll(void);

/**
 * @brief Adds active button to list.
 * 
 * @param floor The floor of the button.
 * 
 * @param orderType Type of the order.
 */
void orderAdd(int floor, HardwareOrder orderType);

/**
 * @brief Clears all orders at given @p floor.
 * 
 * @param floor The floor to be cleared of orders.
 */
void orderClear(int floor);

/**
 * @brief Clears all orders at all floors.
 */
void orderClearAll(void);

/**
 * @brief Is used in orderAdd to update the queue.
 */
void orderAddToQueue(void);

/**
 * @brief Removes the finished queue order and leftshifts once. Used in orderClear.
 */ 
void orderShiftQueue(void);

#endif