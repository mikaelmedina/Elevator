#include "timerControl.h"

Timer timerStartTimer(int milliSec) {
    Timer timer;
    timer.timerStart = clock();
    timer.timerDuration =  timer.timerStart + milliSec/1000 * CLOCKS_PER_SEC;
    return timer;
}