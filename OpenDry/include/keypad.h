#ifndef KEYPAD_H
#include "opendry.h"
extern QueueHandle_t inputQueue;
void keypadInit();
void captureInput(void* arg);
int getInput();
#endif