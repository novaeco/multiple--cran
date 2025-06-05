#include "i2c_driver.h"

#include "esp_log.h"

void i2c_driver_scan(i2c_port_t port) {
    for (uint8_t addr = 1; addr < 0x7F; ++addr) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(port, cmd, pdMS_TO_TICKS(50));
        i2c_cmd_link_delete(cmd);
        if (ret == ESP_OK) {
            ESP_LOGI("i2c", "Périphérique détecté à 0x%02X", addr);
        }
    }

void i2c_driver_scan(i2c_port_t port) {
    // TODO: implémenter le scan I2C
    (void)port;

}
