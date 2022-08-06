#pragma once

#include <SDL.h>

#include "InputManger.h"
#include "Projectile.h"
#include "CGame.h"
<<<<<<< HEAD
//#include "Entity.h"
//#include "Healthbar.h"
//#include "Health.h"
=======
#include "Healthbar.h"
#include "Health.h"
>>>>>>> 94f87c873c403aba84a2369421c75bfb476ffe8a

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