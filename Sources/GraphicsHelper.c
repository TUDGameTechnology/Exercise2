#include <limits.h>
#include <string.h>

#include <kinc/graphics1/graphics.h>
#include <kinc/io/filereader.h>
#include <kinc/math/core.h>

#include "GraphicsHelper.h"

void clear(float red, float green, float blue) {
	for (int y = 0; y < kinc_g1_height(); ++y) {
		for (int x = 0; x < kinc_g1_width(); ++x) {
			kinc_g1_set_pixel(x, y, red, green, blue);
		}
	}
}

int read_pixel(uint8_t* image, int image_width, int image_height, int x, int y) {
	int c = *(int*)&(image)[image_width * 4 * y + x * 4];
	int a = (c >> 24) & 0xff;

	int b = (c >> 16) & 0xff;
	int g = (c >> 8) & 0xff;
	int r = c & 0xff;

	return a << 24 | r << 16 | g << 8 | b;
}

void draw_image(uint8_t* image, int image_width, int image_height, int x, int y) {
	int ystart = max(0, -y);
	int xstart = max(0, -x);
	int h = min(image_height, kinc_g1_height() - y);
	int w = min(image_width, kinc_g1_width() - x);
	for (int yy = ystart; yy < h; ++yy) {
		for (int xx = xstart; xx < w; ++xx) {
			int col = read_pixel(image, image_width, image_height, xx, yy);

			float a = ((col >> 24) & 0xff) / 255.0f;
			float r = ((col >> 16) & 0xff) / 255.0f;
			float g = ((col >> 8)  & 0xff) / 255.0f;
			float b = (col & 0xff) / 255.0f;
			kinc_g1_set_pixel(x + xx, y + yy, r, g, b);
		}
	}
}
