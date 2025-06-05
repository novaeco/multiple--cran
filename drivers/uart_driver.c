#include "uart_driver.h"
#include <esp_log.h>

void uart_driver_init(uart_port_t uart_num, int tx_pin, int rx_pin, int baudrate) {
    uart_config_t config = {
        .baud_rate = baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    ESP_ERROR_CHECK(uart_driver_install(uart_num, 256, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
void uart_driver_init(uart_port_t uart_num, int tx_pin, int rx_pin, int baudrate) {
    // TODO: implémenter l'initialisation UART
    (void)uart_num;
    (void)tx_pin;
    (void)rx_pin;
    (void)baudrate;

}
