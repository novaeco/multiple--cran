#include "uart_driver.h"
#include "wifi_driver.h"
#include "ble_driver.h"
#include "i2c_driver.h"
#include "can_driver.h"
#include "rs485_driver.h"
#include "screen_detect.h"
#include "sd_card.h"
#include "battery.h"
#include "ui.h"
#include "lvgl.h"
#include "esp_timer.h"
#include <string.h>
#include <stdlib.h>

// Tampon simulant le framebuffer LCD
static lv_color_t *lcd_buffer;

static void my_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t w = area->x2 - area->x1 + 1;
    for (int y = area->y1; y <= area->y2; y++) {
        memcpy(&lcd_buffer[y * drv->hor_res + area->x1], color_p, w * sizeof(lv_color_t));
        color_p += w;
    }
    lv_disp_flush_ready(drv);
}

void app_main(void) {
    // Initialisation LVGL
    lv_init();

    // Initialisation des pilotes
    uart_driver_init(UART_NUM_0, 1, 3, 115200);
    wifi_driver_init();
    wifi_driver_connect(NULL, NULL);
    ble_driver_init();
    i2c_driver_init(I2C_NUM_0, 6, 7, 400000);
    i2c_driver_scan(I2C_NUM_0);
    can_driver_init();
    rs485_driver_init(UART_NUM_1, 10, 9, 8, 9600);

    // Modules
    screen_detect_init();
    size_t buf_size = screen_get_width() * screen_get_height() * sizeof(lv_color_t);
    lcd_buffer = malloc(buf_size);

    // Configuration simple du driver d'affichage
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[LV_HOR_RES_MAX * 40];
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LV_HOR_RES_MAX * 40);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screen_get_width();
    disp_drv.ver_res = screen_get_height();
    disp_drv.flush_cb = my_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    sd_card_init();
    battery_update();

    // Interface utilisateur
    ui_init();

    // Boucle principale pour LVGL
    while (1) {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
