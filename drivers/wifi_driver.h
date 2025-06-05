#pragma once
#include <esp_wifi.h>
#include <esp_err.h>


// Initialisation de la pile Wi-Fi
void wifi_driver_init(void);

// Connexion en utilisant les identifiants fournis ou ceux stockés en NVS.
// Si ssid et pass ne sont pas NULL, ils sont sauvegardés en NVS.
// Retourne ESP_OK si la connexion a réussi
esp_err_t wifi_driver_connect(const char *ssid, const char *pass);

