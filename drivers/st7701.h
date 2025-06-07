#pragma once
#include <driver/spi_master.h>
#include <esp_err.h>

typedef struct {
    uint8_t cmd;
    const uint8_t *data;
    uint8_t datalen;
    uint8_t delay_ms;
} st7701_init_cmd_t;

esp_err_t st7701_init(spi_device_handle_t spi);
