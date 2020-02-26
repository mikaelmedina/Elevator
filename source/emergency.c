#include "emergency.h"

int emergencyPollStop(int* pQueue, Elevator* pElevator) {
    int returnValue = 0;
    if(hardware_read_stop_signal()) {
        returnValue = 1;
        hardware_command_stop_light(1);
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        orderClearAll(pQueue, pElevator);
        pElevator->state = ELEVATOR_STOPPED;
        while(hardware_read_stop_signal()) {
            if(elevatorPollFloor() != NO_FLOOR) {
                doorOpen();
                returnValue = 2;
            }
        }
        hardware_command_stop_light(0);
        if(returnValue == 2) {
            Timer timer = timerStartTimer(3000);
            while(clock() < timer.timerDuration) {
                //Keep door open for 3 sec after stop was let go
            }
            doorClose();
        }
        pElevator->state = ELEVATOR_STANDBY;
        return returnValue;
    }
    hardware_command_stop_light(0);
    return returnValue;
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