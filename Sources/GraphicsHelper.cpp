#include "pch.h"
#include "GraphicsHelper.h"
#include <Kore/IO/FileReader.h>
#include <Kore/IO/FileReader.h>
#include <Kore/Graphics1/Graphics.h>
#include <Kore/Graphics1/Image.h>
#include <Kore/Math/Core.h>

#include <limits>
#include <string.h>

using namespace Kore;

void clear(float red, float green, float blue) {
	for (int y = 0; y < Graphics1::height(); ++y) {
		for (int x = 0; x < Graphics1::width(); ++x) {
			Graphics1::setPixel(x, y, red, green, blue);
		}
	}
}

void loadImage(const char* filename, u8* memory, int* imageWidth, int* imageHeight) {
	Graphics1::Image image(filename, true);
	*imageWidth = image.width;
	*imageHeight = image.height;
	memcpy(memory, image.data, image.dataSize);
}

int readPixel(Kore::u8* image, int imageWidth, int imageHeight, int x, int y) {
	int c = *(int*)&(image)[imageWidth * 4 * y + x * 4];
	int a = (c >> 24) & 0xff;

	int b = (c >> 16) & 0xff;
	int g = (c >> 8) & 0xff;
	int r = c & 0xff;

	return a << 24 | r << 16 | g << 8 | b;
}

void drawImage(Kore::u8* image, int imageWidth, int imageHeight, int x, int y) {
	int ystart = max(0, -y);
	int xstart = max(0, -x);
	int h = min(imageHeight, Graphics1::height() - y);
	int w = min(imageWidth, Graphics1::width() - x);
	for (int yy = ystart; yy < h; ++yy) {
		for (int xx = xstart; xx < w; ++xx) {
			int col = readPixel(image, imageWidth, imageHeight, xx, yy);

			float a = ((col >> 24) & 0xff) / 255.0f;
			float r = ((col >> 16) & 0xff) / 255.0f;
			float g = ((col >> 8)  & 0xff) / 255.0f;
			float b = (col & 0xff) / 255.0f;
			Graphics1::setPixel(x + xx, y + yy, r, g, b);
		}
	}
}
