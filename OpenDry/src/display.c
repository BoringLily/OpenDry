#include "display.h"


/* OLED Settings */
SSD1306_t oled_object;

char *DRY_STATES[5] = {"Idle   ", "Preheat", "Drying ", "Cooling", "Error  "};

void setupDisplay(Opendry_Handle_t * opendry_h)
{
    i2c_master_init(&oled_object, OLED_SDA, OLED_SCL, -1);
    ssd1306_init(&oled_object, 128, 64);
    ssd1306_clear_screen(&oled_object, false);
}

void updateMenu(Opendry_Handle_t * opendry_h)
{
    switch (getInput())
    {
        case input_up:
            
            switch (opendry_h->currentMenu)
            {
            case menu_options_back:
                opendry_h->currentMenu = (opendry_h->systemState == idle_s) ? menu_options_start : menu_options_stop;
                break;
            case menu_options_temp:
                opendry_h->currentMenu = menu_options_back;
                break;
            case menu_options_time:
                opendry_h->currentMenu = menu_options_temp;
                break;
            case menu_options_start:
                opendry_h->currentMenu = menu_options_time;
                break;
            case menu_options_stop:
                opendry_h->currentMenu = menu_options_time;
                break;
            case menu_time: 
                opendry_h->runHours += opendry_h->runHours < MAX_RUN_HOURS? 1: 0;
                break;
            case menu_temp: 
                opendry_h->setTemp += opendry_h->setTemp < HEATER_MAX_TEMP? 1: 0;
                break;
            default:
                break;
            }

            break;
        case input_down:
            switch (opendry_h->currentMenu)
            {
            case menu_options_back:
                opendry_h->currentMenu = menu_options_temp;
                break;
            case menu_options_temp:
                opendry_h->currentMenu = menu_options_time;
                break;
            case menu_options_time:
                opendry_h->currentMenu = (opendry_h->systemState == idle_s) ? menu_options_start : menu_options_stop;
                break;
            case menu_options_start:
                opendry_h->currentMenu = menu_options_back;
                break;
            case menu_options_stop:
                opendry_h->currentMenu = menu_options_back;
                break;
            case menu_time: 
                opendry_h->runHours -= opendry_h->runHours > 0 ? 1: 0;
                break;
            case menu_temp: 
                opendry_h->setTemp -= opendry_h->setTemp > 0 ? 1: 0;
                break;
            default:
                break;
            }

            break;
        case input_select:
            switch (opendry_h->currentMenu)
            {
            case menu_dash_idle:
                opendry_h->currentMenu = menu_options_back;
                break;
            case menu_dash_run:
                opendry_h->currentMenu = menu_options_back;
                break;
            case menu_options_back:
                opendry_h->currentMenu = (opendry_h->systemState == idle_s) ? menu_dash_idle : menu_dash_run;
                break;
            case menu_options_temp:
                opendry_h->currentMenu = menu_temp;
                break;
            case menu_options_time:
                opendry_h->currentMenu = menu_time;
                break;
            case menu_options_start:
                opendry_h->currentMenu = menu_dash_run;
                opendry_h->systemState = preheat_s;
                break;
            case menu_options_stop:
                 opendry_h->currentMenu = menu_dash_idle;
                 opendry_h->systemState = cooling_s;
                 break;
            case menu_temp: 
                opendry_h->currentMenu = menu_options_temp;
                break;
            case menu_time: 
                opendry_h->currentMenu = menu_options_time;
                break;
            default:
                break;
            }

            break;
        default:
            break;
    };
    
}

void updateDisplay(Opendry_Handle_t * opendry_h)
{
    #define MSG_ROW 8
    #define MSG_COL 16

    // Display can only print 8 lines on the display lines 0 to 7.

    char msg[MSG_ROW][MSG_COL]; // Display menu buffer

    // Clear display menu buffer
    for (uint8_t i = 0; i < MSG_ROW; i++)
    {
        for(uint8_t j = 0; j < MSG_COL; j++)
        {
            msg[i][j] = ' ';
        }
    }
    
    // updateMenu(opendry_h);

    switch (opendry_h->currentMenu)
    {
    case menu_dash_idle:
        sprintf(msg[1], "Temp: %.0fC\n", opendry_h->temperature);
        sprintf(msg[3], "Humidity: %.0f%%\n", opendry_h->humidity);
        sprintf(msg[7], "State: %s\n", DRY_STATES[opendry_h->systemState]);
        break;
    case menu_dash_run:
        sprintf(msg[1], "Temp: %.0f/%dC\n", opendry_h->temperature, opendry_h->setTemp);
        sprintf(msg[3], "Humidity: %.0f%%\n", opendry_h->humidity);
        sprintf(msg[5], "Time: %d hours\n", opendry_h->runHours);
        sprintf(msg[7], "State: %s\n", DRY_STATES[opendry_h->systemState]);
        break;
    case menu_options_back:
            sprintf(msg[1], "  >   Back   <  \n");
            sprintf(msg[3], "  [ Set Temp ]  \n");
            sprintf(msg[4], "  [ Set Time ]  \n");
            sprintf(msg[5], "  [  %s   ]   \n", opendry_h->systemState == idle_s? "Start": "Stop ");
        break;
    case menu_options_temp:
            sprintf(msg[0], "  [   Back   ]  \n");
            sprintf(msg[2], "  > Set Temp <  \n");
            sprintf(msg[4], "  [ Set Time ]  \n");
            sprintf(msg[5], "  [  %s   ]   \n", opendry_h->systemState == idle_s? "Start": "Stop ");
        break;
    case menu_options_time:
            sprintf(msg[0], "  [   Back   ]  \n");
            sprintf(msg[1], "  [ Set Temp ]  \n");
            sprintf(msg[3], "  > Set Time <  \n");
            sprintf(msg[5], "  [  %s   ]  \n", opendry_h->systemState == idle_s? "Start": "Stop ");
        break;
    case menu_options_start:
            sprintf(msg[0], "  [   Back   ]  \n");
            sprintf(msg[1], "  [ Set Temp ]  \n");
            sprintf(msg[2], "  [ Set Time ]  \n");
            sprintf(msg[4], "  >  Start   <  \n");
        break;
    case menu_options_stop:
            sprintf(msg[0], "  [   Back   ]  \n");
            sprintf(msg[1], "  [ Set Temp ]  \n");
            sprintf(msg[2], "  [ Set Time ]  \n");
            sprintf(msg[4], "  >  Stop    <  \n");
        break;
    case menu_temp:
            sprintf(msg[0], "----Set Temp----\n");
            sprintf(msg[3], "      [%d]      \n", opendry_h->setTemp);
            sprintf(msg[6], "________________\n");
            sprintf(msg[7], "| + | save | - |\n");
            break;
    case menu_time:
            sprintf(msg[0], "----Set Time----\n");
            sprintf(msg[3], "      [%d]      \n", opendry_h->runHours);
            sprintf(msg[6], "________________\n");
            sprintf(msg[7], "| + | save | - |\n");
            break;
    default:
        break;
    }

    ssd1306_contrast(&oled_object, 0xff);
    ssd1306_display_text(&oled_object, 0, msg[0], MSG_COL, false);
    ssd1306_display_text(&oled_object, 1, msg[1], MSG_COL, false);
    ssd1306_display_text(&oled_object, 2, msg[2], MSG_COL, false);
    ssd1306_display_text(&oled_object, 3, msg[3], MSG_COL, false);
    ssd1306_display_text(&oled_object, 4, msg[4], MSG_COL, false);
    ssd1306_display_text(&oled_object, 5, msg[5], MSG_COL, false);
    ssd1306_display_text(&oled_object, 6, msg[6], MSG_COL, false);
    ssd1306_display_text(&oled_object, 7, msg[7], MSG_COL, false);
}