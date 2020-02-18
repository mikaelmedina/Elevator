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

void elevatorArrival(int floor) {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_floor_indicator_on(floor);
    orderClear(floor);
    
    //STATE STOPPED/OPERATING
    doorOpen();
    Timer timer = timerStartTimer(3000);
    while(clock() < timer.timerDuration) {
        if(emergencyPollObstruction()) {
            timer = timerStartTimer(3000);
        }
        orderPoll();
        orderClear(floor);
    }
    doorClose();
}

int elevatorArrivedAtFloor(int floor) {
    if(hardware_read_floor_sensor(floor)) {
        elevatorArrival(floor);
        return 1;
    }
    return 0;
}

void elevatorMovement(int floor) {
    int currentFloor = elevatorPollFloor();
    // set global variable destination = floor;
    if(currentFloor > floor) {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    } else {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    }
}

void elevatorExecuteOrder() {
    //Set state to where elevator is going
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

    // Change 1 to current order being executed
    if(elevatorArrivedAtFloor(1)) {
        //elevatorArrival()
    }
}