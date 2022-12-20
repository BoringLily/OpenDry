#define OPENDRY_CONFIG_H

/* GPIO Pins */

#define HEATER_TEMP_SENSOR GPIO_NUM_5
#define ENCLOSURE_SENSOR GPIO_NUM_4
#define HEATER_RELAY GPIO_NUM_7
#define FAN_RELAY GPIO_NUM_6
#define OLED_SCL GPIO_NUM_0
#define OLED_SDA GPIO_NUM_1
#define USER_INPUT_UP GPIO_NUM_10
#define USER_INPUT_SELECT GPIO_NUM_3
#define USER_INPUT_DOWN GPIO_NUM_2



/* USB serial Settings */

#define MSG_BUFFER_LENGTH 30
#define WRITE_UART_MSG 1
#define INPUT_TYPE 1



/* Operation Settings */

#define HEATER_MAX_TEMP 80 // Heater shutoff temp
#define MAX_RUN_HOURS 12 // Maximum time for a single dry session
#define DEFAULT_RUN_HOURS 4
#define DEFAULT_RUN_TEMP 40