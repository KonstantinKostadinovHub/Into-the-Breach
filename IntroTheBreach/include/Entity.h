#pragma once

#include <iostream>
#include "SDL.h"
#include "Globals.h"
#include "Engine.h"

class Entity {
public:
	Entity();
	Entity(int st_tileCol, int st_tileRow);
	~Entity();

	SDL_Texture* m_texture;
	SDL_Rect m_rect;

	std::pair<int, int> m_curTile;
	int2 grid2dCoords;

	void draw(SDL_Renderer* renderer);
	void moveToTile(int tileCol, int tileRow);
	void setIsometricCoords(int2 centerCoords);
};