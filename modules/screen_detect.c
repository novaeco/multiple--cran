#include "screen_detect.h"
#include "i2c_driver.h"
#include "esp_log.h"
#include "lvgl.h"

static const char *TAG = "screen";
static int s_width = 800;
static int s_height = 480;

void screen_detect_init(void) {
    // Exemple simplifié : détection par lecture d'une GPIO
    bool is_lcd5b = gpio_get_level(GPIO_NUM_2); // Hypothétique pin de détection

    if (is_lcd5b) {
        ESP_LOGI(TAG, "Écran 1024x600 détecté");
        s_width = 1024;
        s_height = 600;
    } else {
        ESP_LOGI(TAG, "Écran 800x480 détecté");
        s_width = 800;
        s_height = 480;
    }
    lv_disp_set_resolution(NULL, s_width, s_height);
}

int screen_get_width(void) {
    return s_width;
}

int screen_get_height(void) {
    return s_height;

void screen_detect_init(void) {
    // TODO: implémenter la détection d'écran et l'initialisation LVGL
}
