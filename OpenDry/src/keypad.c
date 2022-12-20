#include "keypad.h"
QueueHandle_t inputQueue;
intr_handle_t inputInterHandle = NULL;

void keypadInit()
{
    gpio_reset_pin(USER_INPUT_DOWN);
    gpio_reset_pin(USER_INPUT_UP);
    gpio_reset_pin(USER_INPUT_SELECT);

    gpio_config_t pConfig; // pinConfig struct

    pConfig.mode = GPIO_MODE_INPUT;
    pConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    pConfig.pull_down_en = GPIO_PULLDOWN_ENABLE; 
    pConfig.intr_type = GPIO_INTR_DISABLE;

    pConfig.pin_bit_mask = BIT(USER_INPUT_DOWN);
    gpio_config(&pConfig);

    pConfig.pin_bit_mask = BIT(USER_INPUT_SELECT);
    gpio_config(&pConfig);

    pConfig.pin_bit_mask = BIT(USER_INPUT_UP);
    gpio_config(&pConfig);

    //ESP_ERROR_CHECK(esp_intr_alloc(17, ESP_INTR_FLAG_LEVEL3, captureInput, NULL, &inputInterHandle));

    //inputQueue = xQueueCreate(20,sizeof(uint8_t));
}

void captureInput(void* arg)
{
    bool down, up, select;

    down = (bool)gpio_get_level(USER_INPUT_DOWN);

    up = (bool)gpio_get_level(USER_INPUT_UP);

    select = (bool)gpio_get_level(USER_INPUT_SELECT);

    if(select)
    {
        xQueueSendFromISR(inputQueue, (const void*)input_select, NULL);
    }
    if(up)
    {
        xQueueSendFromISR(inputQueue, (const void*)input_up, NULL);
    }
    if(down)
    {
        xQueueSendFromISR(inputQueue, (const void*)input_down, NULL);
    }
}

int getInput()
{
    bool down, up, select;

    down = (bool)gpio_get_level(USER_INPUT_DOWN);

    up = (bool)gpio_get_level(USER_INPUT_UP);

    select = (bool)gpio_get_level(USER_INPUT_SELECT);

    if(select)
    {
        return (int)input_select;
    }
    if(up)
    {
        return (int)input_up;
    }
    if(down)
    {
        return (int)input_down;
    }

    return 99;
}