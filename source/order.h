/**
 * @file 
 * @brief Library with order and queue utilities
 * 
 */

#ifndef ORDER_H
#define ORDER_H
#include "hardware.h"

void orderPoll(void);

/**
 * @brief 
 */
void orderAdd(int floor, HardwareOrder orderType);

/**
 * @brief 
 */
void orderClear(int floor);

void orderClearAll(void);

#endif