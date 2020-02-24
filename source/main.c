#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timerControl.h"
#include "elevatorControl.h"
#include "doorControl.h"
#include "order.h"
#include "emergency.h"


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
        elevatorMainLoop(floorQueue, &elevator);
        signal(SIGINT, sigint_handler);
    }

    return 0;
}
