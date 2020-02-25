#include "order.h"
int ordersInside[HARDWARE_NUMBER_OF_FLOORS];
int ordersDown[HARDWARE_NUMBER_OF_FLOORS];
int ordersUp[HARDWARE_NUMBER_OF_FLOORS];

void orderPoll(int *pQueue, Elevator *pElevator) {
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                orderAdd(f, HARDWARE_ORDER_INSIDE, pQueue, pElevator);
            }
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                orderAdd(f, HARDWARE_ORDER_DOWN, pQueue, pElevator);
            }
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                orderAdd(f, HARDWARE_ORDER_UP, pQueue, pElevator);
            }
        }
}

void orderAdd(int floor, HardwareOrder orderType, int *pQueue, Elevator *pElevator) { 
    if (hardware_read_order(floor, orderType)) {
        switch(orderType) {
            case HARDWARE_ORDER_INSIDE:
                ordersInside[floor] = 1;
                hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
                orderAddToQueue(pQueue, pElevator);
                break;
            case HARDWARE_ORDER_UP:
                ordersUp[floor] = 1;
                hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
                orderAddToQueue(pQueue, pElevator);
                break;
            case HARDWARE_ORDER_DOWN:
                ordersDown[floor] = 1;
                hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
                orderAddToQueue(pQueue, pElevator);
                break;
        }
    }
}

void orderClear(int floor, int *pQueue, Elevator *pElevator) {
    orderShiftQueue(pQueue, pElevator);
    ordersInside[floor] = 0;
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
    ordersUp[floor] = 0;
    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    ordersDown[floor] = 0;
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
}

void orderClearAll(int *pQueue, Elevator *pElevator) {
    for (int f=0; f<HARDWARE_NUMBER_OF_FLOORS; f++) {
        orderClear(f, pQueue, pElevator);
    }
}

void orderAddToQueue(int *pQueue, Elevator *pElevator) {
    int queueIndex = 0;
    switch (pElevator->state) {
        case (ELEVATOR_GOING_UP):
            for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++) {
                if ((ordersInside[f]==1||ordersUp[f]==1)&&(f>pElevator->currentFloor)) {
                    *(pQueue+queueIndex) = f;
                    queueIndex++;
                }
            }
            break;
        case (ELEVATOR_GOING_DOWN):
            for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++) {
                if ((ordersInside[f]==1||ordersDown[f]==1)&&(f<pElevator->currentFloor)) {
                    *(pQueue+queueIndex) = f;
                    queueIndex++;
                }
            }
            break;
        case (ELEVATOR_STANDBY):
            for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++) {
                if (ordersInside[f]==1||ordersUp[f]==1||ordersDown[f]==1) {
                    *(pQueue+queueIndex) = f;
                    queueIndex++;
                }
            }
            break;
        default:
            break;
    }
}

void orderShiftQueue(int *pQueue, Elevator *pElevator) {
    if (*pQueue == pElevator->currentFloor) {
        *pQueue = *(pQueue+1);
        *(pQueue+1) = *(pQueue+2);
        *(pQueue+2) = *(pQueue+3);
        *(pQueue+3) = NO_FLOOR;
    }
}