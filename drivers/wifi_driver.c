#include "wifi_driver.h"
#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <nvs_flash.h>
#include <nvs.h>
#include <string.h>
#include <stdlib.h>

static const char *TAG = "wifi";

void wifi_driver_init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi initialis\xC3\xA9 en mode STA");
}

static void save_credentials(const char *ssid, const char *pass) {
    nvs_handle_t handle;
    if (nvs_open("wifi", NVS_READWRITE, &handle) == ESP_OK) {
        nvs_set_str(handle, "ssid", ssid);
        nvs_set_str(handle, "pass", pass);
        nvs_commit(handle);
        nvs_close(handle);
    }
}

esp_err_t wifi_driver_connect(const char *new_ssid, const char *new_pass) {
    nvs_handle_t handle;
    char ssid[32] = "";
    char pass[64] = "";

    if (new_ssid && new_pass) {
        strncpy(ssid, new_ssid, sizeof(ssid) - 1);
        strncpy(pass, new_pass, sizeof(pass) - 1);
        save_credentials(ssid, pass);
    } else if (nvs_open("wifi", NVS_READONLY, &handle) == ESP_OK) {
        size_t len = sizeof(ssid);
        nvs_get_str(handle, "ssid", ssid, &len);
        len = sizeof(pass);
        nvs_get_str(handle, "pass", pass, &len);
        nvs_close(handle);
    } else {
        ESP_LOGE(TAG, "Aucun identifiant Wi-Fi disponible");
        return ESP_ERR_INVALID_STATE;
    }

    wifi_config_t cfg = {0};
    strncpy((char *)cfg.sta.ssid, ssid, sizeof(cfg.sta.ssid));
    strncpy((char *)cfg.sta.password, pass, sizeof(cfg.sta.password));
    esp_err_t err = esp_wifi_set_config(WIFI_IF_STA, &cfg);
    if (err != ESP_OK) return err;

    err = esp_wifi_scan_start(NULL, true);
    if (err != ESP_OK) return err;

    uint16_t ap_num = 0;
    err = esp_wifi_scan_get_ap_num(&ap_num);
    if (err == ESP_OK && ap_num > 0) {
        wifi_ap_record_t *recs = calloc(ap_num, sizeof(wifi_ap_record_t));
        if (esp_wifi_scan_get_ap_records(&ap_num, recs) == ESP_OK) {
            for (int i = 0; i < ap_num; ++i) {
                ESP_LOGI(TAG, "AP d\xC3\xA9tect\xC3\xA9: %s", recs[i].ssid);
            }
        }
        free(recs);
    }

    err = esp_wifi_connect();
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Connexion au r\xC3\xA9seau %s", ssid);
    }
    return err;
}
