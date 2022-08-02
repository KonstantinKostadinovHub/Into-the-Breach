#pragma once

#include <SDL.h>

#include "InputManger.h"

class CWorld {
public:
	CWorld();
	~CWorld();

	bool m_run;

	SDL_Window* m_mainWindow;
	SDL_Renderer* m_mainRenderer;

	InputManager m_inputManager;

	void init();
	void update();
	void draw();
	void quit();
};