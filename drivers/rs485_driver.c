#include "rs485_driver.h"
#include "driver/gpio.h"

void rs485_driver_init(uart_port_t uart_num, int tx_pin, int rx_pin, int de_pin, int baudrate) {
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

    gpio_set_direction(de_pin, GPIO_MODE_OUTPUT);
    uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX);
void rs485_driver_init(uart_port_t uart_num, int tx_pin, int rx_pin, int de_pin, int baudrate) {
    // TODO: implémenter la gestion RS485
    (void)uart_num;
    (void)tx_pin;
    (void)rx_pin;
    (void)de_pin;
    (void)baudrate;
}
