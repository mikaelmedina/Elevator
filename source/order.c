#include "order.h"
int ordersInside[HARDWARE_NUMBER_OF_FLOORS];
int ordersDown[HARDWARE_NUMBER_OF_FLOORS];
int ordersUp[HARDWARE_NUMBER_OF_FLOORS];


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
        switch(orderType) {
            case HARDWARE_ORDER_INSIDE:
                ordersInside[floor-1] = 1;
                hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
                break;
            case HARDWARE_ORDER_UP:
                ordersUp[floor-1] = 1;
                hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
                break;
            case HARDWARE_ORDER_DOWN:
                ordersDown[floor-1] = 1;
                hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
                break;
        }
    }
}

void orderClear(int floor) {
    ordersInside[floor-1] = 0;
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
    ordersUp[floor-1] = 0;
    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    ordersDown[floor-1] = 0;
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
}

void orderClearAll(void) {
    for (int f=1; f<5; f++) {
        orderClear(f);
    }
}