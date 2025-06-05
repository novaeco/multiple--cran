#pragma once
#include "driver/i2c.h"

// Initialisation du bus I2C
void i2c_driver_init(i2c_port_t port, int sda, int scl, uint32_t freq);

// Scan I2C et affichage des adresses détectées
void i2c_driver_scan(i2c_port_t port);
