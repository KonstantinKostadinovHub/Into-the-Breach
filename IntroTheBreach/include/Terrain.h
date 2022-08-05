#pragma once

#include "SDL.h"
#include "Globals.h"
#include "Engine.h"

class Terrain {
public:
	Terrain();
	Terrain(int st_tileCol, int st_tileRow);
	~Terrain();

	SDL_Texture* m_texture;
	SDL_Rect m_rect;
	int2 grid2dCoords;

	std::pair<int, int> m_curTile;

	void draw(SDL_Renderer* renderer);
	void setIsometricCoords(int2 centerCoords);
};