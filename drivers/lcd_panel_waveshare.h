#pragma once
#include <esp_lcd_panel_ops.h>
#include <stdint.h>

// Initialise le panneau LCD Waveshare et renvoie le handle
esp_lcd_panel_handle_t lcd_panel_waveshare_init(int width, int height);
