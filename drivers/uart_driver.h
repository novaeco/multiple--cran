#pragma once
#include "driver/uart.h"

// Initialisation UART avec paramètres configurables
void uart_driver_init(uart_port_t uart_num, int tx_pin, int rx_pin, int baudrate);
