#pragma once

#include "SDL.h"
#include "Globals.h"
#include "Engine.h"

class Health {
public:
	Health();
	Health(int2 coords, int w);
	~Health();

	static SDL_Texture* m_HEALTH_TEXTURE;
	SDL_Rect m_rect;

	void draw(SDL_Renderer* renderer);
	void moveCoords(int2 coordsChange);
};