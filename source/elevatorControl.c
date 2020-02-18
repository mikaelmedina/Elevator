#include "elevatorControl.h"

int elevatorPollFloor(void) {
    for(int floor = 1; floor < 5; floor++) {
        if(hardware_read_floor_sensor(floor)) {
            return floor;
        }
    }
    return 0;
}

int elevatorToKnownState(void) {
    while(!elevatorPollFloor) {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);

    //
    // Set state to standby 
    //

    return elevatorPollFloor();
}

void elevatorMainLoop(void) {
    if(emergencyPollStop() && elevatorPollFloor()) {
        Timer timer = timerStartTimer(3000);
        while(clock() < timer.timerDuration) {
            orderPoll();
        }
        doorClose();
    }
    orderPoll();
}