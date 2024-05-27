#pragma once

#include <stdint.h>

// Clears the screen to a single color
void clear(float red, float green, float blue);

// Draws 32bit RGBA pixels (for examples the ones loaded via loadImage)
void draw_image(uint8_t* image, int image_width, int image_height, int x, int y);
