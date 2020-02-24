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

void elevatorArrival(int floor, int* pQueue, Elevator* pElevator) {
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_floor_indicator_on(floor);
    orderClear(floor, pQueue, pElevator);
    
    //STATE STOPPED/OPERATING
    pElevator->currentFloor = floor;
    if(*pQueue != NO_FLOOR) {
        pElevator->nextFloor = *pQueue;
    }
    doorOpen();

    Timer timer = timerStartTimer(3000);
    while(clock() < timer.timerDuration) {
        if(emergencyPollObstruction()) {
            timer = timerStartTimer(3000);
        }
        orderPoll(pQueue, pElevator);
        orderClear(floor, pQueue, pElevator);
    }
    doorClose();
}

int elevatorArrivedAtFloor(int floor) {
    if(hardware_read_floor_sensor(floor)) {
        return 1;
    }
    return 0;
}

void elevatorMovement(Elevator* pElevator) {
    if(pElevator->nextFloor < pElevator->currentFloor) {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        pElevator->state = ELEVATOR_GOING_DOWN;
    } 
    else if(pElevator->nextFloor > pElevator->currentFloor) {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        pElevator->state = ELEVATOR_GOING_UP;
    } 
    else {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        pElevator->state = ELEVATOR_STANDBY;
    }
}

void elevatorExecuteOrder(int* pQueue, Elevator* pElevator) {
    if(pElevator->currentFloor == pElevator->nextFloor) {

    }
}




void elevatorMainLoop(int* pQueue, Elevator* pElevator) {
    if(emergencyPollStop(pQueue, pElevator) && elevatorPollFloor() != NO_FLOOR) {
        Timer timer = timerStartTimer(3000);
        while(clock() < timer.timerDuration) {
            orderPoll(pQueue, pElevator);
        }
        doorClose();
    }
    orderPoll(pQueue, pElevator);

    elevatorExecuteOrder(pQueue, pElevator);



    elevatorMovement(pElevator);

    if(elevatorArrivedAtFloor(pElevator->nextFloor)) {
        elevatorArrival(pElevator->nextFloor, pQueue, pElevator);
    }
}