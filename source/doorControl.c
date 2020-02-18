#include "doorControl.h"

void doorOpen(void) {
    hardware_command_door_open(1);
}


void doorClose(void) {
    if(!hardware_read_obstruction_signal()) {
        hardware_command_door_open(0);
    }
}