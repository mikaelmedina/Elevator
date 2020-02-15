#include "hardware.h"

/**
 * @brief Commands the hardware to open the door and set the floor 
 *  indicator to the given floor.
 *
 * @param floor int value of the desired floor indicator to turn on, 
 * if the value is 0 nothing happens.
 * @param open truthy value to open the door, 0 to close it. 
 */
void doorOpen(int floor, int open);

