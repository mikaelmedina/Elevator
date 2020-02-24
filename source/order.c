#include "order.h"
extern int ordersInside[HARDWARE_NUMBER_OF_FLOORS];
extern int ordersDown[HARDWARE_NUMBER_OF_FLOORS];
extern int ordersUp[HARDWARE_NUMBER_OF_FLOORS];
extern int queue[HARDWARE_NUMBER_OF_FLOORS];


void orderPoll(void) {
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                orderAdd(f, HARDWARE_ORDER_INSIDE);
            }
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                orderAdd(f, HARDWARE_ORDER_DOWN);
            }
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                orderAdd(f, HARDWARE_ORDER_UP);
            }
        }
}

void orderAdd(int floor, HardwareOrder orderType) { 
    if (hardware_read_order(floor, orderType)) {
        orderAddToQueue();
        switch(orderType) {
            case HARDWARE_ORDER_INSIDE:
                ordersInside[floor-1] = 1;
                hardware_command_order_light(floor-1, HARDWARE_ORDER_INSIDE, 1);
                break;
            case HARDWARE_ORDER_UP:
                ordersUp[floor-1] = 1;
                hardware_command_order_light(floor-1, HARDWARE_ORDER_UP, 1);
                break;
            case HARDWARE_ORDER_DOWN:
                ordersDown[floor-1] = 1;
                hardware_command_order_light(floor-1, HARDWARE_ORDER_DOWN, 1);
                break;
        }
    }
}

void orderClear(int floor) {
    orderShiftQueue();
    ordersInside[floor-1] = 0;
    hardware_command_order_light(floor-1, HARDWARE_ORDER_INSIDE, 0);
    ordersUp[floor-1] = 0;
    hardware_command_order_light(floor-1, HARDWARE_ORDER_UP, 0);
    ordersDown[floor-1] = 0;
    hardware_command_order_light(floor-1, HARDWARE_ORDER_DOWN, 0);
}

void orderClearAll(void) {
    for (int f=1; f<5; f++) {
        orderClear(f);
    }
}

void orderAddToQueue(void) {
    /* funcSetDirection(); */
    int queueIndex = 0;
    if (elevatorState == ELEVATOR_GOING_UP) {
        for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++) {
            if ((ordersInside[f]==1||ordersUp[f]==1)&&(f+1>elevatorCurrentFloor)) {
                queue[queueIndex] = f+1;
                queueIndex++;
            }
        }
    }
    else if (elevatorState == ELEVATOR_GOING_DOWN) {
        for (int f=0;f<HARDWARE_NUMBER_OF_FLOORS;f++) {
            if ((ordersInside[f]==1||ordersDown[f]==1)&&(f+1<elevatorCurrentFloor)) {
                queue[queueIndex] = f+1;
                queueIndex++;
            }
        }
    }
}

void orderShiftQueue(void) {
    if (queue[0]==elevatorCurrentFloor-1) {
        queue[0] = queue[1];
        queue[1] = queue[2];
        queue[2] = queue[3];
        queue[3] = 0;
    }
}