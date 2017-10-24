#include "pch.h"
#include "GraphicsHelper.h"
#include <Kore/IO/FileReader.h>
#include <Kore/IO/FileReader.h>
#include <Kore/Graphics4/Graphics.h>
#include <Kore/Graphics1/Graphics.h>
#include <Kore/Math/Core.h>
#include <limits>

using namespace Kore;

namespace {
	Graphics4::Texture* texture;
	int* image;
}

void clear(float red, float green, float blue) {
	for (int y = 0; y < Graphics1::height(); ++y) {
		for (int x = 0; x < Graphics1::width(); ++x) {
			Graphics1::setPixel(x, y, red, green, blue);
		}
	}
}

Graphics4::Texture* loadTexture(const char* filename) {
	return new Graphics4::Texture(filename, true);
}

void destroyTexture(Graphics4::Texture* image) {
	delete image;
}

void drawTexture(Graphics4::Texture* inImage, int x, int y) {
	int ystart = max(0, -y);
	int xstart = max(0, -x);
	int h = min(inImage->height, Graphics1::height() - y);
	int w = min(inImage->width, Graphics1::width() - x);
	for (int yy = ystart; yy < h; ++yy) {
		for (int xx = xstart; xx < w; ++xx) {
			int col = readPixel(inImage, xx, yy);

			float a = ((col >> 24) & 0xff) / 255.0f;
			float r = ((col >> 16) & 0xff) / 255.0f;
			float g = ((col >> 8)  & 0xff) / 255.0f;
			float b = (col & 0xff) / 255.0f;
			Graphics1::setPixel(x + xx, y + yy, r, g, b);// , a);
		}
	}
}

int readPixel(Graphics4::Texture* image, int x, int y) {
	int c = *(int*)&((u8*)image->data)[image->texWidth * 4 * y + x * 4];
	int a = (c >> 24) & 0xff;

	int b = (c >> 16) & 0xff;
	int g = (c >> 8) & 0xff;
	int r = c & 0xff;

	return a << 24 | r << 16 | g << 8 | b;
}
