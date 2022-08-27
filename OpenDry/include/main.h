#define MAIN_H

#include "driver/gpio.h"

/* System Pins */
#define HEATER_TEMP GPIO_NUM_6
#define ENCLOSURE_TEMP GPIO_NUM_5
#define HEATER_RELAY GPIO_NUM_7
#define FAN_RELAY GPIO_NUM_4
#define OLED_SCL GPIO_NUM_0
#define OLED_SDA GPIO_NUM_1
#define USER_INPUT_UP GPIO_NUM_10
#define USER_INPUT_SELECT GPIO_NUM_3
#define USER_INPUT_DOWN GPIO_NUM_2

/* System Config Settings */

#define USE_ENCODER 1

