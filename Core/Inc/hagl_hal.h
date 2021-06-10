#pragma once

#include "lcd.h"
#include "bitmap.h"

#define DISPLAY_WIDTH 	(128)		// ustawienie wyświetlacza
#define DISPLAY_HEIGHT 	(160)
#define DISPLAY_DEPTH 	16

typedef uint16_t color_t;

#define hagl_hal_put_pixel lcd_put_pixel
