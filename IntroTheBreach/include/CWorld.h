#pragma once

#include <SDL.h>

class CWorld {
public:
	CWorld();
	~CWorld();

	bool m_run;

	SDL_Window* m_mainWindow;
	SDL_Renderer* m_mainRenderer;

	void init();
	void update();
	void draw();
	void suicide();
};