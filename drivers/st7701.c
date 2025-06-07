#include "st7701.h"
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const uint8_t init_cmd0[] = {0x77, 0x01, 0x00, 0x00, 0x00};
static const uint8_t init_cmd1[] = {0x77, 0x01, 0x00, 0x00, 0x10};
static const uint8_t init_cmd2[] = {0x63, 0x00};
static const uint8_t init_cmd3[] = {0x10, 0x02};
static const uint8_t init_cmd4[] = {0x37, 0x08};
static const uint8_t init_cmd5[] = {0x38};
static const uint8_t init_cmd6[] = {0x40,0xC9,0x90,0x0D,0x0F,0x04,0x00,0x07,0x07,0x1C,0x04,0x52,0x0F,0xDF,0x26,0xCF};
static const uint8_t init_cmd7[] = {0x40,0xC9,0xCF,0x0C,0x90,0x04,0x00,0x07,0x08,0x1B,0x06,0x55,0x13,0x62,0xE7,0xCF};
static const uint8_t init_cmd8[] = {0x77, 0x01, 0x00, 0x00, 0x11};
static const uint8_t init_cmd9[] = {0x5D};
static const uint8_t init_cmd10[] = {0x2D};
static const uint8_t init_cmd11[] = {0x07};
static const uint8_t init_cmd12[] = {0x80};
static const uint8_t init_cmd13[] = {0x08};
static const uint8_t init_cmd14[] = {0x85};
static const uint8_t init_cmd15[] = {0x20};
static const uint8_t init_cmd16[] = {0x10};
static const uint8_t init_cmd17[] = {0x78};
static const uint8_t init_cmd18[] = {0x78};
static const uint8_t init_cmd19[] = {0x88};
static const uint8_t init_cmd20[] = {0x00,0x19,0x02};
static const uint8_t init_cmd21[] = {0x05,0xA0,0x07,0xA0,0x04,0xA0,0x06,0xA0,0x00,0x44,0x44};
static const uint8_t init_cmd22[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t init_cmd23[] = {0x00,0x00,0x33,0x33};
static const uint8_t init_cmd24[] = {0x44,0x44};
static const uint8_t init_cmd25[] = {0x0D,0x31,0xC8,0xAF,0x0F,0x33,0xC8,0xAF,0x09,0x2D,0xC8,0xAF,0x0B,0x2F,0xC8,0xAF};
static const uint8_t init_cmd26[] = {0x00,0x00,0x33,0x33};
static const uint8_t init_cmd27[] = {0x44,0x44};
static const uint8_t init_cmd28[] = {0x0C,0x30,0xC8,0xAF,0x0E,0x32,0xC8,0xAF,0x08,0x2C,0xC8,0xAF,0x0A,0x2E,0xC8,0xAF};
static const uint8_t init_cmd29[] = {0x02,0x00,0xE4,0xE4,0x44,0x00,0x40};
static const uint8_t init_cmd30[] = {0x3C,0x00};
static const uint8_t init_cmd31[] = {0xAB,0x89,0x76,0x54,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x10,0x45,0x67,0x98,0xBA};
static const uint8_t init_cmd32[] = {0x77,0x01,0x00,0x00,0x00};

static const st7701_init_cmd_t init_cmds[] = {
    {0xFF, init_cmd0, sizeof(init_cmd0), 0},
    {0x13, NULL, 0, 0},
    {0xEF, (uint8_t[]){0x08}, 1, 0},
    {0xFF, init_cmd1, sizeof(init_cmd1), 0},
    {0xC0, init_cmd2, sizeof(init_cmd2), 0},
    {0xC1, init_cmd3, sizeof(init_cmd3), 0},
    {0xC2, init_cmd4, sizeof(init_cmd4), 0},
    {0xCC, init_cmd5, sizeof(init_cmd5), 0},
    {0xB0, init_cmd6, sizeof(init_cmd6), 0},
    {0xB1, init_cmd7, sizeof(init_cmd7), 0},
    {0xFF, init_cmd8, sizeof(init_cmd8), 0},
    {0xB0, init_cmd9, sizeof(init_cmd9), 0},
    {0xB1, init_cmd10, sizeof(init_cmd10), 0},
    {0xB2, init_cmd11, sizeof(init_cmd11), 0},
    {0xB3, init_cmd12, sizeof(init_cmd12), 0},
    {0xB5, init_cmd13, sizeof(init_cmd13), 0},
    {0xB7, init_cmd14, sizeof(init_cmd14), 0},
    {0xB8, init_cmd15, sizeof(init_cmd15), 0},
    {0xB9, init_cmd16, sizeof(init_cmd16), 0},
    {0xC1, init_cmd17, sizeof(init_cmd17), 0},
    {0xC2, init_cmd18, sizeof(init_cmd18), 0},
    {0xD0, init_cmd19, sizeof(init_cmd19), 100},
    {0xE0, init_cmd20, sizeof(init_cmd20), 0},
    {0xE1, init_cmd21, sizeof(init_cmd21), 0},
    {0xE2, init_cmd22, sizeof(init_cmd22), 0},
    {0xE3, init_cmd23, sizeof(init_cmd23), 0},
    {0xE4, init_cmd24, sizeof(init_cmd24), 0},
    {0xE5, init_cmd25, sizeof(init_cmd25), 0},
    {0xE6, init_cmd26, sizeof(init_cmd26), 0},
    {0xE7, init_cmd27, sizeof(init_cmd27), 0},
    {0xE8, init_cmd28, sizeof(init_cmd28), 0},
    {0xEB, init_cmd29, sizeof(init_cmd29), 0},
    {0xEC, init_cmd30, sizeof(init_cmd30), 0},
    {0xED, init_cmd31, sizeof(init_cmd31), 0},
    {0xFF, init_cmd32, sizeof(init_cmd32), 0},
    {0x11, NULL, 0, 120},
    {0x29, NULL, 0, 50},
};

static esp_err_t send_cmd(spi_device_handle_t spi, const st7701_init_cmd_t *cmd) {
    spi_transaction_t t = {
        .cmd = 0,
        .addr = cmd->cmd,
        .length = 0,
        .rxlength = 0,
        .flags = 0,
    };
    esp_err_t ret = spi_device_transmit(spi, &t);
    if (ret != ESP_OK) return ret;
    if (cmd->datalen > 0) {
        for (int i = 0; i < cmd->datalen; i++) {
            spi_transaction_t td = {
                .cmd = 1,
                .addr = cmd->data[i],
                .length = 0,
                .rxlength = 0,
                .flags = 0,
            };
            ret = spi_device_transmit(spi, &td);
            if (ret != ESP_OK) return ret;
        }
    }
    if (cmd->delay_ms) {
        vTaskDelay(pdMS_TO_TICKS(cmd->delay_ms));
    }
    return ESP_OK;
}

esp_err_t st7701_init(spi_device_handle_t spi) {
    for (size_t i = 0; i < sizeof(init_cmds)/sizeof(init_cmds[0]); i++) {
        esp_err_t ret = send_cmd(spi, &init_cmds[i]);
        if (ret != ESP_OK) return ret;
    }
    return ESP_OK;
}
