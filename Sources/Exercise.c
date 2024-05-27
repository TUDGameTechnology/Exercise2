#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <kinc/audio1/audio.h>
#include <kinc/audio2/audio.h>
#include <kinc/graphics1/graphics.h>
#include <kinc/io/filereader.h>
#include <kinc/math/core.h>
#include <kinc/system.h>

#include "GraphicsHelper.h"

#define WIDTH 512
#define HEIGHT 512

double start_time;

uint8_t* memory;

// Add more simple variables if you like to
// but put bigger things in memory.
// Avoid allocations.
int image_width;
int image_height;

void init() {
	// Load more images if you like but keep their size in mind.
	// This only supports 32bit RGBA files, so the size in memory is width * height * 4.
	load_image("irobert-fb.png", memory, &image_width, &image_height);

	// Please replace the sound
	kinc_a1_sound_stream_t* sound = kinc_a1_sound_stream_create("back.ogg", true);
	kinc_a1_play_sound_stream(sound);
}

void update(void* data) {
	float t = (float)(kinc_time() - start_time);
	kinc_a2_update();

	kinc_g1_begin();

	/************************************************************************/
	/* Exercise 2, Practical Task:
	/* Add some interesting animations or effects here.
	/* GraphicsHelper.h has some new helper functions.
	/************************************************************************/
	clear(0.0f, 0.0f, 0.0f);
	draw_image(memory, image_width, image_height, (int)(sin(t) * 400), (int)(abs(sin(t * 1.5f)) * 470));

	kinc_g1_end();
}

int kickstart(int argc, char** argv) {
	kinc_init("Exercise 2", WIDTH, HEIGHT, NULL, NULL);

	kinc_g1_init(WIDTH, HEIGHT);
	kinc_set_update_callback(update, NULL);

	start_time = kinc_time();

	kinc_a1_init();

	memory = malloc(10 * 1024 * 1024); // 10 MiB of memory - should be enough for anything
	init();

	kinc_start();

	return EXIT_SUCCESS;
}
