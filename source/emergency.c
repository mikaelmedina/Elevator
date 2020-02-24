#include "emergency.h"

int emergencyPollStop(int* pQueue, Elevator* pElevator) {
    if(hardware_read_stop_signal()) {
        hardware_command_stop_light(1);
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        orderClearAll(pQueue, pElevator);
        while(hardware_read_stop_signal()) {
            if(elevatorPollFloor() != NO_FLOOR) {
                openDoor();
            }
        }
        hardware_command_stop_light(0);
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
    hardware_command_stop_light(0);
    return 0;
}