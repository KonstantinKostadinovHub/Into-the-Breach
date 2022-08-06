#pragma once

#include <SDL.h>

#include "InputManger.h"
#include "CGame.h"
//#include "Entity.h"
//#include "Healthbar.h"
//#include "Health.h"

class CWorld {
public:
	CWorld();
	~CWorld();

	bool m_run;

	SDL_Window* m_mainWindow;
	SDL_Renderer* m_mainRenderer;

	InputManager m_inputManager;
	CGame m_game;

	void init();
	void update();
	void draw();
	void quit();
};