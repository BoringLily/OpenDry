#include "opendry.h"

#define TAG "OpenDry"

void opendryInit(Opendry_Handle_t * opendry_h)
{
    opendry_h->addrCount = (size_t)0;
    opendry_h->runHours = DEFAULT_RUN_HOURS;
    opendry_h->setTemp = DEFAULT_RUN_TEMP;
    opendry_h->temperature = 0.12;
    opendry_h->heaterTemp = 0.0;
    opendry_h->systemState = idle_s;
    opendry_h->currentMenu = menu_dash_idle;
}

void opendryBegin(Opendry_Handle_t * opendry_h)
{
    //serial_init();
   gpio_reset_pin(HEATER_TEMP_SENSOR);
   gpio_reset_pin(ENCLOSURE_SENSOR);
   
    setupDisplay(opendry_h);
    keypadInit();
}

void readSensors(Opendry_Handle_t *opendry_h)
{
    //temporary variables
    int16_t temp, humidity;
    float heater;

    if(opendry_h->addrCount == 0)
    {
        size_t adrC;
        ds18x20_addr_t adrF;
        ESP_ERROR_CHECK(ds18x20_scan_devices(HEATER_TEMP_SENSOR, &adrF, 1, &adrC));

        if(adrC == 0)
        {
            serial_out("ERROR->Heater temp sensor not found\n");
            vTaskDelay(500/portTICK_PERIOD_MS);
        }
        else
        {
            opendry_h->addrCount = adrC;
            opendry_h->heaterAddress = adrF;
        }
    }
    else
    {

        ESP_ERROR_CHECK(ds18x20_measure(HEATER_TEMP_SENSOR, DS18X20_ANY, true));

        ESP_ERROR_CHECK(ds18b20_read_temperature(HEATER_TEMP_SENSOR, opendry_h->heaterAddress, &heater));

        ESP_ERROR_CHECK(dht_read_data(DHT_TYPE_AM2301, ENCLOSURE_SENSOR, &humidity, &temp));

        opendry_h->heaterTemp = heater;
        opendry_h->temperature = (temp/10.0);
        opendry_h->humidity = (humidity/10.0);
    }
}

void controller(Opendry_Handle_t * opendry_h)
{
    switch(opendry_h->systemState)
    {
    case idle_s:
        opendry_h->currentMenu = opendry_h->currentMenu == menu_dash_run ? menu_dash_idle: opendry_h->currentMenu;
        break;
    case preheat_s:
        opendry_h->systemState = opendry_h->temperature < (opendry_h->setTemp-5) ? drying_s : drying_s;
        break;
    case drying_s:
        opendry_h->systemState = opendry_h->runHours == 0 ? cooling_s : drying_s;
        break;
    case cooling_s:
        opendry_h->systemState = ((opendry_h->temperature < 30) && (opendry_h->heaterTemp < 30)) ? idle_s : cooling_s;
        break;
    default:
        break;
    }
}


