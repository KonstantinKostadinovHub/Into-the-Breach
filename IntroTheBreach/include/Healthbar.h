#pragma once

#include <vector>
#include "SDL.h"
#include "Globals.h"
#include "Health.h"

class Healthbar {
public:
	Healthbar();
	Healthbar(int health, int2 centerCoords, bool enemy);
	~Healthbar();

	static SDL_Texture* m_HEALTHBAR_TEXTURE;
	SDL_Rect m_rect;
	int m_maxHealth;

	std::vector<Health> m_health;

	bool m_enemy;

	bool m_healthDepleted;

	void draw(SDL_Renderer* renderer);
	void decreaseHealth(int decrease);
	void setCoords(int2 coords);
};