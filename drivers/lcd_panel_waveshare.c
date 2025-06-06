#include "lcd_panel_waveshare.h"
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_lcd_panel_rgb.h>
#include <esp_log.h>

#define PIN_NUM_PCLK  40
#define PIN_NUM_CS    41
#define PIN_NUM_DE    42
#define PIN_NUM_VSYNC 39
#define PIN_NUM_HSYNC 38
#define PIN_NUM_DATA0 0

static const char *TAG = "lcd_panel";

esp_lcd_panel_handle_t lcd_panel_waveshare_init(int width, int height) {
#if SOC_LCD_RGB_SUPPORTED
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
            PIN_NUM_DATA0, PIN_NUM_DATA0 + 1, PIN_NUM_DATA0 + 2, PIN_NUM_DATA0 + 3,
            PIN_NUM_DATA0 + 4, PIN_NUM_DATA0 + 5, PIN_NUM_DATA0 + 6, PIN_NUM_DATA0 + 7,
            PIN_NUM_DATA0 + 8, PIN_NUM_DATA0 + 9, PIN_NUM_DATA0 + 10, PIN_NUM_DATA0 + 11,
            PIN_NUM_DATA0 + 12, PIN_NUM_DATA0 + 13, PIN_NUM_DATA0 + 14, PIN_NUM_DATA0 + 15
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
    return handle;
#else
    ESP_LOGW(TAG, "RGB LCD non supporté sur cette cible");
    return NULL;
#endif
}
