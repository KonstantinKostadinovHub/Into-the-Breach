#pragma once

#include <string>
#include <SDL.h>

using std::string;

#include "Engine.h"
#include "InputManger.h"

class CTile {
public:
	CTile();
	~CTile();

	static int m_gridSize;

	int z_add;

	bool hovered;

	SDL_Renderer* m_mainRenderer;

	SDL_Texture* m_texture;

	button m_button;
	SDL_Rect m_rectLifted;
	SDL_Rect m_isomRect;
	SDL_Rect m_isomRectLifted;

	void init(SDL_Renderer* renderer, SDL_Texture* texture, int2 coord, int size);
	void update();
	void draw();
	void quit();
};