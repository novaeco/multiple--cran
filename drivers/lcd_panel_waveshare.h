#pragma once
#include <esp_lcd_panel_ops.h>
#include <stdint.h>

/*
 * Initialise le panneau LCD Waveshare et renvoie le handle.
 * Les broches de contrôle DISP et LCD_RST peuvent être définies via
 * les macros PIN_NUM_DISP et PIN_NUM_LCD_RST. Laisser ces macros à
 * -1 désactive la gestion des broches correspondantes.
 */
esp_lcd_panel_handle_t lcd_panel_waveshare_init(int width, int height);
