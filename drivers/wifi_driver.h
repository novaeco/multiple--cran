#pragma once

#include "esp_wifi.h"

// Initialisation de la pile Wi-Fi
void wifi_driver_init(void);
// Connexion en utilisant les identifiants fournis ou ceux stockés en NVS.
// Si ssid et pass ne sont pas NULL, ils sont sauvegardés en NVS.
void wifi_driver_connect(const char *ssid, const char *pass);


// Connexion en utilisant les identifiants fournis ou ceux stockés en NVS.
// Si ssid et pass ne sont pas NULL, ils sont sauvegardés en NVS.
void wifi_driver_connect(const char *ssid, const char *pass);


// Connexion avec SSID/mot de passe stockés en NVS
void wifi_driver_connect(void);
// Connexion Wi-Fi en mode station automatique
void wifi_driver_init(void);


