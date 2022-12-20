#include "serialMonitor.h"

esp_err_t serial_init()
{
    uart_port_t uart_num = UART_NUM_0;
    //Create UART config struct
    uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
    .rx_flow_ctrl_thresh = 122
    };

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, 0, 10, &uart_queue, 0));

    if(uart_is_driver_installed(UART_NUM_0))
    {
        return ESP_OK;
    }
    else
    {
        return ESP_ERR_TIMEOUT;
    }
}

esp_err_t serial_out(char * strBuffer)
{
    uart_port_t uart_num = UART_NUM_0;

    uart_write_bytes(uart_num, strBuffer, (size_t)strlen(strBuffer));
    //uart_wait_tx_done((uart_port_t)UART_NUM_0,);
    //uart_flush(uart_num);
    vTaskDelay(200/portTICK_PERIOD_MS);
    return ESP_OK;
}