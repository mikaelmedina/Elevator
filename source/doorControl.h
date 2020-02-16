/**
 * @file
 * @brief Library with door control.
 * 
*/


#ifndef DOORCONTROL_H
#define DOORCONTROL_H
#include "hardware.h"

/**
 * @brief Commands the hardware to open the door.
 *
 */
void doorOpen(void);

/**
 * @brief Commands the hardware to close the door.
 *
 */
void doorClose(void);

#endif