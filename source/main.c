#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timerControl.h"
#include "doorControl.h"
#include "order.h"
#include "elevatorControl.h"


static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
   



    int floorQueue[HARDWARE_NUMBER_OF_FLOORS];
    Elevator elevator;

    int startFloor = elevatorToKnownState(&elevator);

    elevator.currentFloor = elevator.nextFloor = startFloor;
    elevator.state = ELEVATOR_STANDBY;

    while(1){
        elevatorMainLoop(&floorQueue, &elevator);
        signal(SIGINT, sigint_handler);
    }

    return 0;
}
