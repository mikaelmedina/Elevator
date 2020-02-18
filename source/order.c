#include "order.h"
int ordersInside[HARDWARE_NUMBER_OF_FLOORS];
int ordersDown[HARDWARE_NUMBER_OF_FLOORS];
int ordersUp[HARDWARE_NUMBER_OF_FLOORS];

void orderAdd(Order order) { 
    if (hardware_read_order(order.floor, order.orderType)) {
        switch(order.orderType) {
            case HARDWARE_ORDER_INSIDE:
                ordersInside[order.floor-1] = 1;
                break;
            case HARDWARE_ORDER_UP:
                ordersUp[order.floor-1] = 1;
                break;
            case HARDWARE_ORDER_DOWN:
                ordersDown[order.floor-1] = 1;
        }
    }
}

void orderClear(int floor) {
    ordersInside[floor-1] = 0;
    ordersUp[floor-1] = 0;
    ordersDown[floor-1] = 0;
}