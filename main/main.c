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

void app_main(void) {
    // Initialisation des pilotes
    uart_driver_init(UART_NUM_0, 1, 3, 115200);
    wifi_driver_init();
    ble_driver_init();
    i2c_driver_scan(I2C_NUM_0);
    can_driver_init();
    rs485_driver_init(UART_NUM_1, 10, 9, 8, 9600);

    // Modules
    screen_detect_init();
    sd_card_init();
    battery_update();

    // Interface utilisateur
    ui_init();
}
