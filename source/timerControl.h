/**
 * @file
 * @brief Library with timer utilities
 * 
*/

#ifndef TIMERCONTROL_H
#define TIMERCONTROL_H

#include <time.h>

/**
 * @brief A struct that holds start time of a timer and desired duration.
 */

typedef struct {
    clock_t timerStart;     /**< The time when timer started. */
    clock_t timerDuration;  /**< When the timer should stop. */
} Timer;


/**
 * @brief Creates a timer struct which holds time when timer started, 
 * and time when timer should end.
 * 
 * @param milliSec How many milliseconds to count.
 * 
 * @return Timer struct.
*/
Timer timerStartTimer(int milliSec);

#endif