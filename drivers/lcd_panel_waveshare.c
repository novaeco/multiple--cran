#include "lcd_panel_waveshare.h"
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_lcd_panel_rgb.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIN_NUM_PCLK  7
#define PIN_NUM_DE    5
#define PIN_NUM_VSYNC 3
#define PIN_NUM_HSYNC 46
#ifndef PIN_NUM_DISP
#define PIN_NUM_DISP  -1
#endif
#ifndef PIN_NUM_LCD_RST
#define PIN_NUM_LCD_RST -1
#endif

#if SOC_LCD_RGB_SUPPORTED
// Mapping 16-bit RGB565 data bus using Waveshare pinout
static const int data_pins[16] = {
    14, 38, 18, 17, 10,     // B3..B7
    39, 0, 45, 48, 47, 21,  // G2..G7 (G3 on GPIO0)
    1, 2, 42, 41, 40        // R3..R7
};
#endif

static const char *TAG = "lcd_panel";

esp_lcd_panel_handle_t lcd_panel_waveshare_init(int width, int height) {
#if SOC_LCD_RGB_SUPPORTED

    if (PIN_NUM_DISP >= 0) {
        gpio_config_t conf = {
            .pin_bit_mask = 1ULL << PIN_NUM_DISP,
            .mode = GPIO_MODE_OUTPUT,
        };
        gpio_config(&conf);
        gpio_set_level(PIN_NUM_DISP, 0);
    }

    if (PIN_NUM_LCD_RST >= 0) {
        gpio_config_t conf = {
            .pin_bit_mask = 1ULL << PIN_NUM_LCD_RST,
            .mode = GPIO_MODE_OUTPUT,
        };
        gpio_config(&conf);
        gpio_set_level(PIN_NUM_LCD_RST, 0);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(PIN_NUM_LCD_RST, 1);
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    esp_lcd_rgb_panel_config_t panel_config = {
        .data_width = 16,
        .psram_trans_align = 64,
        .num_fbs = 1,
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .disp_gpio_num = PIN_NUM_DE,
        .pclk_gpio_num = PIN_NUM_PCLK,
        .vsync_gpio_num = PIN_NUM_VSYNC,
        .hsync_gpio_num = PIN_NUM_HSYNC,
        .data_gpio_nums = {
            data_pins[0], data_pins[1], data_pins[2], data_pins[3],
            data_pins[4], data_pins[5], data_pins[6], data_pins[7],
            data_pins[8], data_pins[9], data_pins[10], data_pins[11],
            data_pins[12], data_pins[13], data_pins[14], data_pins[15]
        },
        .timings = {
            .pclk_hz = 9 * 1000 * 1000,
            .h_res = width,
            .v_res = height,
        }
    };

    esp_lcd_panel_handle_t handle = NULL;
    esp_err_t ret = esp_lcd_new_rgb_panel(&panel_config, &handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Erreur initialisation panneau %d", ret);
        return NULL;
    }
    esp_lcd_panel_reset(handle);
    esp_lcd_panel_init(handle);
    esp_lcd_panel_invert_color(handle, true);

    if (PIN_NUM_DISP >= 0) {
        gpio_set_level(PIN_NUM_DISP, 1);
    }

    esp_lcd_panel_disp_on_off(handle, true);
    return handle;
#else
    ESP_LOGW(TAG, "RGB LCD non supporté sur cette cible");
    return NULL;
#endif
}
