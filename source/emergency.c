#include "emergency.h"

int emergencyPollStop(int* pQueue, Elevator* pElevator) {
    int returnValue = 0;
    if(hardware_read_stop_signal()) {
        pElevator->state = ELEVATOR_STOPPED;
        returnValue = 1;
        hardware_command_stop_light(1);
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        orderClearAll(pQueue, pElevator);
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
                if(emergencyPollObstruction()) {
                    timer = timerStartTimer(3000);
                }
            }
            
        }
        pElevator->state = ELEVATOR_STANDBY;
        doorClose();
        return returnValue;
    }
    hardware_command_stop_light(0);
    return returnValue;
}

int emergencyPollObstruction(void) {
    // && state is door open
    if(hardware_read_obstruction_signal()) {
        return 1;
    }
    return 0;
}