#pragma once
#include "driver/uart.h"

// Communication RS485 en demi-duplex
void rs485_driver_init(uart_port_t uart_num, int tx_pin, int rx_pin, int de_pin, int baudrate);
