#ifndef OPENDRY_TYPES_H
#define OPENDRY_TYPES_H
//#pragma once
#include <string.h>           

/* typedefs begin */

/*
    @brief System operation statse enum
*/
typedef enum systemState_t 
{
    idle_s,
    preheat_s,
    drying_s,
    cooling_s,
    error_s
}systemState_t;

typedef enum menu_t
{
    menu_dash_idle,
    menu_dash_run,
    menu_options_back,
    menu_options_temp,
    menu_options_time,
    menu_options_start,
    menu_options_stop,
    menu_temp,
    menu_time
}menu_t;

typedef enum userInput_t
{
    input_up,
    input_down,
    input_select
}userInput_t;

/*
    @brief OpenDry system data object

    @param setTemp User Set Temperature
    @param heaterTemp Heater Temperature
    @param temperature Environment Temperature
    @param humidity
    @param addrCount Number of Heater Sensors Found
    @param heaterAddress Heater Sensor Address
    @param systemState System state
    @param currentMenu Current tdisplayed  Menu state
*/

typedef struct Opendry_Handle_t
{

float heaterTemp;
float temperature;    
float humidity;
uint8_t setTemp;
uint8_t runHours;
size_t addrCount;
ds18x20_addr_t heaterAddress;

systemState_t systemState;
menu_t currentMenu;
} Opendry_Handle_t;

#endif

