#include "pch.h"

#include <Kore/IO/FileReader.h>
#include <Kore/Math/Core.h>
#include <Kore/System.h>
#include <Kore/Audio1/Audio.h>
#include <Kore/Audio2/Audio.h>
#include <Kore/Graphics1/Graphics.h>
#include <Kore/Graphics1/Image.h>
#include "GraphicsHelper.h"

const int width = 512;
const int height = 512;

using namespace Kore;

namespace {
	double startTime;

	u8* memory; // 10 MiB of memory - should be enough for anything
	
	// Add more simple variables if you like to
	// but put bigger things in memory.
	// Avoid any "new".
	int imageWidth;
	int imageHeight;

	void init() {
		// Load more images if you like but keep their size in mind.
		// This only supports 32bit RGBA files, so the size in memory is width * height * 4.
		loadImage("irobert-fb.png", memory, &imageWidth, &imageHeight);
		
		// Please replace the sound
		Kore::Audio1::play(new SoundStream("back.ogg", true));
	}

	void update() {
		float t = (float)(System::time() - startTime);
		Kore::Audio2::update();
		
		Graphics1::begin();

		/************************************************************************/
		/* Exercise 2, Practical Task:
		/* Add some interesting animations or effects here.
		/* GraphicsHelper.h has some new helper functions.
		/************************************************************************/
		clear(0.0f, 0.0f, 0.0f);
		drawImage(memory, imageWidth, imageHeight, (int)(sin(t) * 400), (int)(abs(sin(t * 1.5f)) * 470));

		Graphics1::end();
	}
}

int kore(int argc, char** argv) {
	System::init("Exercise 1", width, height);

	Graphics1::init(width, height);
	Kore::System::setCallback(update);
		
	startTime = System::time();
	
	Kore::Audio2::init();
	Kore::Audio1::init();

	memory = new u8[10 * 1024 * 1024];
	init();

	Kore::System::start();

	return 0;
}
