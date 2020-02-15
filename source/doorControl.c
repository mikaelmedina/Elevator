#include "doorControl.h"

void doorOpen(int floor, int open) {
    if (floor) {
        hardware_command_floor_indicator_on(floor);
    }
    hardware_command_door_open(open);
}