#include "battery.h"
#include <esp_adc/adc_oneshot.h>
#include <esp_log.h>

static const char *TAG = "battery";
static int s_battery_percent = 0;
static const int ADC_MAX = 4095;
static const float VBATT_MAX = 4.2f;
static const float VBATT_MIN = 3.3f;

static adc_oneshot_unit_handle_t s_adc_handle;

void battery_update(void) {
    if (!s_adc_handle) {
        adc_oneshot_unit_init_cfg_t init_cfg = {
            .unit_id = ADC_UNIT_1,
        };
        adc_oneshot_new_unit(&init_cfg, &s_adc_handle);

        adc_oneshot_chan_cfg_t chan_cfg = {
            .bitwidth = ADC_BITWIDTH_DEFAULT,
            .atten = ADC_ATTEN_DB_12,
        };
        adc_oneshot_config_channel(s_adc_handle, ADC_CHANNEL_0, &chan_cfg);
    }

    int raw = 0;
    adc_oneshot_read(s_adc_handle, ADC_CHANNEL_0, &raw);
    float voltage = (raw / (float)ADC_MAX) * VBATT_MAX;
    if (voltage < VBATT_MIN) voltage = VBATT_MIN;
    s_battery_percent = (int)(((voltage - VBATT_MIN) / (VBATT_MAX - VBATT_MIN)) * 100);
    ESP_LOGI(TAG, "Niveau batterie: %d%%", s_battery_percent);
}

int battery_get_percent(void) {
    return s_battery_percent;

}
