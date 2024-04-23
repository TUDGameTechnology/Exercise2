#pragma once

#include <stdint.h>

// Clears the screen to a single color
void clear(float red, float green, float blue);

// Loads an image into the memory pointed to by memory.
// Also sets the width and height parameters to the image dimensions.
void load_image(const char* filename, uint8_t* memory, int* image_width, int* image_height);

// Draws 32bit RGBA pixels (for examples the ones loaded via loadImage)
void draw_image(uint8_t* image, int image_width, int image_height, int x, int y);
