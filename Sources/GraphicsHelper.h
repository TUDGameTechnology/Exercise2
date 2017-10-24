#pragma once

namespace Kore {
	namespace Graphics4 {
		class Texture;
	}
}

void clear(float red, float green, float blue);
Kore::Graphics4::Texture* loadTexture(const char* filename);
void destroyTexture(Kore::Graphics4::Texture* image);
void drawTexture(Kore::Graphics4::Texture* image, int x, int y);
int readPixel(Kore::Graphics4::Texture* image, int x, int y);
