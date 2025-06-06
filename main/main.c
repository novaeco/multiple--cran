#include "uart_driver.h"
#include "wifi_driver.h"
#if CONFIG_BT_BLUEDROID_ENABLED
#include "ble_driver.h"
#endif
#include "i2c_driver.h"
#include "can_driver.h"
#include "rs485_driver.h"
#include "screen_detect.h"
#include "sd_card.h"
#include "battery.h"
#include "ui.h"
#include <lvgl.h>
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"
#include "esp_timer.h"
#include <string.h>
#include <stdlib.h>

/* Framebuffer utilisé par l'exemple. Les données ne sont jamais envoyées
 * vers l'écran sans implémentation spécifique du pilote.
 */
static lv_color_t *lcd_buffer;
static esp_lcd_panel_handle_t s_panel = NULL;
/*
 * Callback LVGL appelé pour rafraîchir l'écran. Ce code copie simplement les
 * pixels dans un tampon. Adapt ez ici pour transmettre effectivement les
 * données au contrôleur LCD (via esp_lcd_panel_draw_bitmap par exemple).
 */

static void my_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    lv_color_t *color_p = (lv_color_t *)px_map;
    uint32_t hor_res = lv_display_get_horizontal_resolution(disp);
    int32_t w = area->x2 - area->x1 + 1;
    for(int32_t y = area->y1; y <= area->y2; y++) {
        memcpy(&lcd_buffer[y * hor_res + area->x1], color_p,
               w * sizeof(lv_color_t));
        color_p += w;

    }
    if (s_panel) {
        esp_lcd_panel_draw_bitmap(s_panel, area->x1, area->y1,
                                  area->x2 + 1, area->y2 + 1,
                                  &lcd_buffer[area->y1 * hor_res + area->x1]);
    }
    lv_display_flush_ready(disp);
}

void app_main(void) {
    lv_init();

    uart_driver_init(UART_NUM_0, 1, 3, 115200);
    wifi_driver_init();
#if CONFIG_BT_BLUEDROID_ENABLED
    ble_driver_init();
#endif
    i2c_driver_init(I2C_NUM_0, 6, 7, 400000);
    can_driver_init();
    rs485_driver_init(UART_NUM_1, 10, 9, 8, 9600);

    screen_detect_init();
    size_t buf_size = screen_get_width() * screen_get_height() * sizeof(lv_color_t);
    lcd_buffer = malloc(buf_size);

    uint32_t width = screen_get_width();
    uint32_t height = screen_get_height();

    lv_display_t *disp = lv_display_create(width, height);
    lv_display_set_flush_cb(disp, my_flush);
    lv_color_t *buf1 = malloc(width * 40 * sizeof(lv_color_t));
    lv_display_set_buffers(disp, buf1, NULL, width * 40 * sizeof(lv_color_t),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);


    sd_card_init();
    wifi_driver_connect(NULL, NULL);
    battery_update();
    ui_init();

    while (1) {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
    }

    free(buf1);
    free(lcd_buffer);
}
