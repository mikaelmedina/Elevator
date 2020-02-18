#include "emergency.h"

int emergencyPollStop(void) {
    if(hardware_read_stop_signal()) {
        hardware_command_stop_light(1);
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        // Remove all orders from the queue
        while(hardware_read_stop_signal()) {}
        return 1;
    }
    hardware_command_stop_light(0);
    return 0;
}

int emergencyPollObstruction(void) {
    // && state is door open
    if(hardware_read_obstruction_signal()) {
        hardware_command_stop_light(1);
        return 1;
    }
    return 0;
}