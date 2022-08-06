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

	string m_type;

	void init(SDL_Renderer* renderer, SDL_Texture* texture, string type, int2 size);
	void giveCentralPoint(int2 coord);
	void update();
	void draw();
	void quit();
};