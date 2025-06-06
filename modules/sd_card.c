#include "sd_card.h"
#include <esp_vfs_fat.h>
#include <sdmmc_cmd.h>
#include <driver/sdmmc_host.h>
#include <driver/sdmmc_defs.h>
#include <esp_log.h>

static const char *TAG = "sd";
static sdmmc_card_t *s_card;

void sd_card_init(void) {
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
    };
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &s_card);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Carte SD montée");
    } else {
        ESP_LOGE(TAG, "Échec montage carte SD: %s", esp_err_to_name(ret));
    }

}

void sd_card_unmount(void) {
    if (s_card) {
        esp_vfs_fat_sdcard_unmount("/sdcard", s_card);
        s_card = NULL;
        ESP_LOGI(TAG, "Carte SD démontée");
    }
}
