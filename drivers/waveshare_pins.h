#pragma once
/* Pin mapping for Waveshare ESP32-S3 Touch LCD boards (5B and 7") */

#define WS_PIN_PCLK   7
#define WS_PIN_DE     5
#define WS_PIN_VSYNC  3
#define WS_PIN_HSYNC  46

// 16-bit RGB565 data bus: B3..B7, G2..G7, R3..R7
#define WS_PIN_B3  14
#define WS_PIN_B4  38
#define WS_PIN_B5  18
#define WS_PIN_B6  17
#define WS_PIN_B7  10

#define WS_PIN_G2  39
#define WS_PIN_G3  0
#define WS_PIN_G4  45
#define WS_PIN_G5  48
#define WS_PIN_G6  47
#define WS_PIN_G7  21

#define WS_PIN_R3  1
#define WS_PIN_R4  2
#define WS_PIN_R5  42
#define WS_PIN_R6  41
#define WS_PIN_R7  40

/* Optional control pins. Set to -1 if unconnected */
#ifndef PIN_NUM_DISP
#define PIN_NUM_DISP    6
#endif
#ifndef PIN_NUM_LCD_RST
#define PIN_NUM_LCD_RST 11
#endif
#ifndef PIN_NUM_LCD_MOSI
#define PIN_NUM_LCD_MOSI 12
#endif
#ifndef PIN_NUM_LCD_CLK
#define PIN_NUM_LCD_CLK 13
#endif
#ifndef PIN_NUM_LCD_CS
#define PIN_NUM_LCD_CS 15
#endif
