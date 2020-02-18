/**
 * @file
 * @brief Library that handles the stop button and obstructions.
 * 
 */

#ifndef EMERGENCY_H
#define EMERGENCY_H
#include "hardware.h"
#include "elevatorControl.h"
#include "doorControl.h"

/**
 * @brief Polls the stop button, sets stop light active and stops
 *  the elevator if button is pressed. Also removes all orders and 
 *  opens the door if at a floor.
 * @return 1 if the button was pressed, 0 otherwise.
 */
int emergencyPollStop(void);

/**
 * @brief Polls the obstruction switch, if there is an obstruction
 * turns on the stoplight.
 * @return 1 if there was an obstruction, 0 otherwise.
*/
int emergencyPollObstruction(void);

#endif