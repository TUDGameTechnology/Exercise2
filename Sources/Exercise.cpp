#include "pch.h"

#include <Kore/IO/FileReader.h>
#include <Kore/Math/Core.h>
#include <Kore/System.h>
#include <Kore/Audio1/Audio.h>
#include <Kore/Graphics1/Graphics.h>
#include "GraphicsHelper.h"

const int width = 512;
const int height = 512;

using namespace Kore;

namespace {
	double startTime;
	Graphics4::Texture* image;

	void init() {
		image = loadTexture("irobert-fb.png");
		Kore::Audio1::play(new SoundStream("back.ogg", true));

	}

	void update() {
		float t = (float)(System::time() - startTime);
		//Kore::Audio1::update();
		
		Graphics1::begin();

		/************************************************************************/
		/* Exercise 2, Practical Task:   
		/* Add some interesting animations or effects here          
		/************************************************************************/
		clear(0.0f, 0.0f, 0.0f);
		drawTexture(image, (int)(sin(t) * 400), (int)(abs(sin(t * 1.5f)) * 470));

		Graphics1::end();
	}
}

int kore(int argc, char** argv) {
	System::init("Exercise 1", width, height);

	Graphics1::init(width, height);
	Kore::System::setCallback(update);
		
	startTime = System::time();
	
	Kore::Audio1::init();

	init();

	Kore::System::start();

	destroyTexture(image);
	
	return 0;
}
