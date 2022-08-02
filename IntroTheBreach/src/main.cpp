#include <SDL.h>

#include <iostream>

using namespace std;

#include "Globals.h"
#include "CWorld.h"

#undef main

int main(int* argc, char* argv[])
{
	getScreenDetails(SCREEN_W, SCREEN_H);

	CWorld world;
	world.init();

	unsigned long long last_update = 0;
	unsigned long long last_draw = 0;

	while (world.m_run)
	{
		if (SDL_GetTicks() >= last_update + 1000 / tps) {
			world.update();
			last_update = SDL_GetTicks();
		}

		if (SDL_GetTicks() >= last_draw + 1000 / fps) {
			world.draw();
			last_draw = SDL_GetTicks();
		}
	}
}