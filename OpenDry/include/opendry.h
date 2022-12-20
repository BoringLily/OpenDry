#ifndef OPENDRY_H
#define OPENDRY_H

#include "opendry_include.h"

TaskHandle_t displayTask_handle;
TaskHandle_t controllerTask_handle;



void displayTask(void * arg);
void controllerTask(void * arg);

void opendryBegin();

void readSensors(Opendry_Handle_t *opendry_h);

void opendryInit(Opendry_Handle_t * opendry_h);

void controller(Opendry_Handle_t * opendry_h);


#endif