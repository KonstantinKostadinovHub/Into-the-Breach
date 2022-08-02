#pragma once

#include <iostream>
#include "SDL.h"
#include "Globals.h"

class Entity {
public:
	Entity();
	Entity(int st_tileRow, int st_tileCol);
	~Entity();

	SDL_Texture* m_texture;
	SDL_Rect m_rect;

	std::pair<int, int> m_curTile;

	void draw(SDL_Renderer* renderer);
	void moveToTile(int tileRow, int tileCol);
};