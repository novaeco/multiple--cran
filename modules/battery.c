#include "battery.h"
#include <driver/adc.h>
#include <esp_log.h>

static const char *TAG = "battery";
static int s_battery_percent = 0;
static const int ADC_MAX = 4095;
static const float VBATT_MAX = 4.2f;
static const float VBATT_MIN = 3.3f;

void battery_update(void) {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    int raw = adc1_get_raw(ADC1_CHANNEL_0);
    float voltage = (raw / (float)ADC_MAX) * VBATT_MAX;
    if (voltage < VBATT_MIN) voltage = VBATT_MIN;
    s_battery_percent = (int)(((voltage - VBATT_MIN) / (VBATT_MAX - VBATT_MIN)) * 100);
    ESP_LOGI(TAG, "Niveau batterie: %d%%", s_battery_percent);
}

int battery_get_percent(void) {
    return s_battery_percent;

}
