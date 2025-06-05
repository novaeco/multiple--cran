
idf_component_register(SRCS
    "uart_driver.c"
    "wifi_driver.c"
    "ble_driver.c"
    "i2c_driver.c"
    "can_driver.c"
    "rs485_driver.c"
    INCLUDE_DIRS "."
    REQUIRES nvs_flash esp_wifi esp_event esp_netif bt driver)
