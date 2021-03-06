#include "elevatorControl.h"

static int elevatorArrivedAtFloor(int floor) {
    if(hardware_read_floor_sensor(floor)) {
        return 1;
    }
    return 0;
}

static void elevatorMovement(int* pQueue, Elevator* pElevator) {
    if(pElevator->state != ELEVATOR_STOPPED && *pQueue != NO_FLOOR) {
        if(pElevator->nextFloor <= pElevator->currentFloor && (*pQueue < pElevator->currentFloor || pElevator->lastFloorState != ELEVATOR_GOING_DOWN)) {
            if(elevatorPollFloor() != NO_FLOOR) {
                pElevator->lastFloorState = ELEVATOR_GOING_DOWN;
            }
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            pElevator->state = ELEVATOR_GOING_DOWN;
        }
        else if(pElevator->nextFloor >= pElevator->currentFloor) {
            if(elevatorPollFloor() != NO_FLOOR) {
                pElevator->lastFloorState = ELEVATOR_GOING_UP;
            }
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
            pElevator->state = ELEVATOR_GOING_UP;
        } 
        else {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            pElevator->state = ELEVATOR_STANDBY;
        }
    }
}

static void elevatorExecuteOrder(int* pQueue, Elevator* pElevator) {
    if((pElevator->state == ELEVATOR_STANDBY && *pQueue > NO_FLOOR) || (pElevator->state == ELEVATOR_STOPPED && *pQueue > NO_FLOOR)) {
        pElevator->nextFloor = *pQueue;
        pElevator->state = ELEVATOR_STANDBY;
    }
}

static void elevatorPassFloor(Elevator* pElevator) {
    static int floor = NO_FLOOR;
    floor = elevatorPollFloor();
    if(floor != NO_FLOOR) {
        pElevator->currentFloor = floor;
    }
}

int elevatorPollFloor(void) {
    for(int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if(hardware_read_floor_sensor(floor)) {
            return floor;
        }
    }
    return NO_FLOOR;
}

int elevatorToKnownState(Elevator* pElevator) {
    while(elevatorPollFloor() == NO_FLOOR) {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    hardware_command_floor_indicator_on(elevatorPollFloor());    
    return elevatorPollFloor();
}

void elevatorArrival(int floor, int* pQueue, Elevator* pElevator) {
    switch(pElevator->state) {
        case(ELEVATOR_STANDBY): {
            break;
        }
        case(ELEVATOR_STOPPED): {
            break;
        }
        default: {
            pElevator->currentFloor = floor;
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_floor_indicator_on(floor);
            orderClear(floor, pQueue, pElevator);


            if(*pQueue != NO_FLOOR) {
                pElevator->nextFloor = *pQueue;
            } else {
                pElevator->state = ELEVATOR_STANDBY;
            }

            doorOpen();
            Timer timer = timerStartTimer(3000);
            while(clock() < timer.timerDuration) {
                if(emergencyPollObstruction()) {
                    timer = timerStartTimer(3000);
                }
                orderPoll(pQueue, pElevator);
                orderClear(floor, pQueue, pElevator);
                emergencyPollStop(pQueue, pElevator);
            }
            doorClose();
            break;
        }
    }
}

void elevatorMainLoop(int* pQueue, Elevator* pElevator) {
    orderPoll(pQueue, pElevator);
    orderAddToQueue(pQueue, pElevator);
    elevatorExecuteOrder(pQueue, pElevator);
    elevatorMovement(pQueue, pElevator);
    emergencyPollStop(pQueue, pElevator);
    elevatorPassFloor(pElevator);
    
    if(elevatorArrivedAtFloor(pElevator->nextFloor)) {
        elevatorArrival(pElevator->nextFloor, pQueue, pElevator);
    }
}