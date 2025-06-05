
set(srcs
    "uart_driver.c"
    "wifi_driver.c"
    "i2c_driver.c"
    "can_driver.c"
    "rs485_driver.c")

set(requires nvs_flash esp_wifi esp_event esp_netif driver)
set(priv_requires "")
set(include_dirs "")

if(CONFIG_BT_BLUEDROID_ENABLED)
    list(APPEND srcs "ble_driver.c")
    list(APPEND requires bt)
    list(APPEND priv_requires bt)
    set(bt_include "$ENV{IDF_PATH}/components/bt/host/bluedroid/api/include/api")
    file(TO_CMAKE_PATH "${bt_include}" bt_include)
    list(APPEND include_dirs "${bt_include}")
endif()

idf_component_register(SRCS ${srcs}
    INCLUDE_DIRS "." ${include_dirs}
    REQUIRES ${requires}
    PRIV_REQUIRES ${priv_requires})
