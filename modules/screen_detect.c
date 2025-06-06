#include "screen_detect.h"
#include "i2c_driver.h"
#include <esp_log.h>
#include <lvgl.h>
#include <driver/gpio.h>
#include <stdbool.h>

static const char *TAG = "screen";
static int s_width = 800;
static int s_height = 480;

void screen_detect_init(void) {
    // Tentative de détection via le contrôleur tactile GT911
    i2c_driver_scan(I2C_NUM_0);
    bool gt911_high = (gpio_get_level(GPIO_NUM_2) == 1);

    if (gt911_high) {
        ESP_LOGI(TAG, "Écran 1024x600 détecté");
        s_width = 1024;
        s_height = 600;
    } else {
        ESP_LOGI(TAG, "Écran 800x480 détecté");
        s_width = 800;
        s_height = 480;
    }

    /*
     * LVGL v9 ne fournit pas d'API pour modifier la resolution d'un ecran
     * deja enregistree. La taille sera donc renseignee lors de
     * l'initialisation du pilote dans main.c.
     */


}

int screen_get_width(void) {
    return s_width;
}

int screen_get_height(void) {
    return s_height;

}
