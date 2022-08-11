#include <ctime>

#include "CWorld.h"

#include "Globals.h"

CWorld::CWorld() {
	srand(time(0));

	m_run = true;
	m_mainWindow = nullptr;
	m_mainRenderer = nullptr;

	m_inputManager = InputManager();
	m_game = CGame();
}

CWorld::~CWorld() {

}

void CWorld::init() {
	m_mainWindow = SDL_CreateWindow("Into the Breach", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, 0);
	m_mainRenderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	Entity::readEntityAssets();
	Projectile::m_PROJECTILE_TEXTURE = loadTexture(m_mainRenderer, "entity\\projectile.bmp");
	Health::m_HEALTH_TEXTURE = loadTexture(m_mainRenderer, "entity\\health.bmp");
	Health::m_ENEMY_HEALTH_TEXTURE = loadTexture(m_mainRenderer, "entity\\enemyHealth.bmp");
	Healthbar::m_HEALTHBAR_TEXTURE = loadTexture(m_mainRenderer, "entity\\healthbar.bmp");

	m_game.init(m_mainRenderer);
}

void CWorld::update() {
	m_inputManager.update();
	m_game.update();
	
	if (InputManager::m_quit) {
		m_run = false;
	}
}

void CWorld::draw() {
	SDL_RenderClear(m_mainRenderer);

	m_game.draw();

	SDL_RenderPresent(m_mainRenderer);
}

void CWorld::quit() {
	m_game.quit();

	SDL_DestroyRenderer(m_mainRenderer);
	SDL_DestroyWindow(m_mainWindow);
}
