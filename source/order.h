/**
 * @file 
 * @brief Library with order and queue utilities
 * 
 */

#ifndef ORDER_H
#define ORDER_H
#include "hardware.h"

typedef struct {
    int floor; /** The destination of the order */
    HardwareOrder orderType; /** Type of order */
} Order;

/**
 * @brief 
 */
void orderAdd(Order order);

/**
 * @brief 
 */
void orderClear(int floor);

#endif