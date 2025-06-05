#include "battery.h"
#include <driver/adc.h>
#include <esp_log.h>

static const char *TAG = "battery";
static int s_battery_percent = 0;

void battery_update(void) {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    int raw = adc1_get_raw(ADC1_CHANNEL_0);
    s_battery_percent = (raw * 100) / 4095;
    ESP_LOGI(TAG, "Niveau batterie: %d%%", s_battery_percent);
}

int battery_get_percent(void) {
    return s_battery_percent;
void battery_update(void) {
    // TODO: implémenter la lecture et l'affichage du niveau de batterie
}
