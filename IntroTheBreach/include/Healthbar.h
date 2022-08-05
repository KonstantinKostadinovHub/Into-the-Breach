#pragma once

#include <vector>
#include "SDL.h"
#include "Globals.h"
#include "Health.h"

class Healthbar {
public:
	Healthbar();
	Healthbar(int health, int2 coords);
	~Healthbar();

	static SDL_Texture* m_HEALTHBAR_TEXTURE;
	SDL_Rect m_rect;
	int m_maxHealth;
	int m_healthLeft;

	std::vector<Health> m_health;

	bool m_delete;

	void draw(SDL_Renderer* renderer);
};