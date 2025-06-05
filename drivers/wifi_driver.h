#pragma once
#include "esp_wifi.h"

// Initialisation de la pile Wi-Fi
void wifi_driver_init(void);

// Connexion avec SSID/mot de passe stockés en NVS
void wifi_driver_connect(void);
