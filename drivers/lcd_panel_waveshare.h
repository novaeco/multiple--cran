#pragma once
#include <esp_lcd_panel_ops.h>
#include <stdint.h>

/*
 * Initialize the Waveshare LCD panel and return a handle.
 * The DISP and LCD_RST control pins can be configured with the
 * macros PIN_NUM_DISP and PIN_NUM_LCD_RST. Set a macro to -1 to
 * disable handling of the corresponding pin.
 */
esp_lcd_panel_handle_t lcd_panel_waveshare_init(int width, int height);
