#pragma once

#include <string>
#include <SDL.h>

using std::string;

#include "Engine.h"

class CTile {
public:
	CTile();
	~CTile();

	static int m_gridSize;

	SDL_Renderer* m_mainRenderer;

	SDL_Texture* m_texture;

	SDL_Rect m_rect;
	SDL_Rect m_isomRect;

	void init(SDL_Renderer* renderer, SDL_Texture* texture, int2 coord, int size);
	void update();
	void draw();
	void quit();
};