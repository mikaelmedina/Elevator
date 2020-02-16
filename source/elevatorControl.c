#include "elevatorControl.h"

int elevatorPollFloor(void) {
    for(int floor = 1; floor < 5; floor++) {
        if(hardware_read_floor_sensor(floor)) {
            return floor;
        }
    }
    return 0;
}