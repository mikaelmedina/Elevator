#include "doorControl.h"

void doorOpen(void) {
    hardware_command_door_open(1);
}


void doorClose(void) {
    hardware_command_door_open(0);
}