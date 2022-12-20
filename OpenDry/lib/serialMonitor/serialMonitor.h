#ifndef __SERIALMONITOR_H__
#define __SERIALMONITOR_H__

#include "driver/uart.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "string.h"


#ifdef __cplusplus
extern "C" {
#endif

esp_err_t serial_init();


esp_err_t serial_out(char * strBuffer);


#ifdef __cplusplus
}
#endif
#endif