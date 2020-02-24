#include "elevatorControl.h"

int elevatorPollFloor(void) {
    for(int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if(hardware_read_floor_sensor(floor)) {
            return floor;
        }
    }
    return NO_FLOOR;
}

int elevatorToKnownState(void) {
    while(elevatorPollFloor() == NO_FLOOR) {
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
    elevatorCurrentFloor = floor;
    if(orderQueue[0] != NO_FLOOR) {
        elevatorNextFloor = orderQueue[0];
    }
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
    if(emergencyPollStop() && elevatorPollFloor() != NO_FLOOR) {
        Timer timer = timerStartTimer(3000);
        while(clock() < timer.timerDuration) {
            orderPoll();
        }
        doorClose();
    }
    orderPoll();

    // Ser på bestillinger og utfører

    // Change 1 to current order being executed
    if(elevatorArrivedAtFloor(elevatorNextFloor)) {
        elevatorArrival(elevatorNextFloor);
        //elevatorArrival()
    }
}