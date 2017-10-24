#pragma once

// Clears the screen to a single color
void clear(float red, float green, float blue);

// Loads an image into the memory pointed to by memory.
// Also sets the width and height parameters to the image dimensions.
void loadImage(const char* filename, Kore::u8* memory, int* width, int* height);

// Draws 32bit RGBA pixels (for examples the ones loaded via loadImage)
void drawImage(Kore::u8* image, int imageWidth, int imageHeight, int x, int y);
