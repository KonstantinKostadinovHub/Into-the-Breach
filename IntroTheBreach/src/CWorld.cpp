#include "CWorld.h"

#include "Globals.h"

CWorld::CWorld() {
	m_inputManager = InputManager();

	m_run = true;
	m_mainWindow = nullptr;
	m_mainRenderer = nullptr;
}

CWorld::~CWorld() {

}

void CWorld::init() {
	m_mainWindow = SDL_CreateWindow("Into the Breach", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, 0);
	m_mainRenderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);
}

void CWorld::update() {
	m_inputManager.update();

	if (InputManager::m_quit) {
		m_run = false;
	}
}

void CWorld::draw() {
	SDL_RenderClear(m_mainRenderer);

	//draw functions

	SDL_RenderPresent(m_mainRenderer);
}

void CWorld::suicide() {
	SDL_DestroyRenderer(m_mainRenderer);
	SDL_DestroyWindow(m_mainWindow);
}
