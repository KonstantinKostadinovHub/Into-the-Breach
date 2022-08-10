#pragma once

#include <string>
#include <SDL.h>

using std::string;

#include "Engine.h"

class CTerrain {
public:
	CTerrain();
	~CTerrain();

	SDL_Renderer* m_mainRenderer;

	SDL_Texture* m_texture;
	SDL_Rect m_rect;

	int m_health;

	virtual string getType();

	virtual void init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size);
	void giveCentralPoint(int2 coord);
	virtual void update();
	virtual void draw();
	virtual void quit();
};