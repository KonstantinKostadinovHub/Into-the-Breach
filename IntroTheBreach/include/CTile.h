#pragma once

#include <string>
#include <SDL.h>

using std::string;

#include "CTerrain.h"
#include "Engine.h"
#include "InputManger.h"

class CTile {
public:
	CTile();
	~CTile();

	static int m_gridSize;

	int z_add;

	bool hovered;
	bool selected;

	bool water;

	SDL_Renderer* m_mainRenderer;

	SDL_Texture* m_texture;
	SDL_Texture* m_shadowTexture;

	button m_button;
	SDL_Rect m_rectLifted;
	SDL_Rect m_isomRect;
	SDL_Rect m_isomRectLifted;

	CTerrain* m_terrain;

	void init(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* shadow_texture, int2 coord, int size, bool is_water, CTerrain* terrain);
	void update();
	void draw();
	void quit();
};