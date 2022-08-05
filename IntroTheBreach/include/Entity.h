#pragma once

#include <iostream>
#include "SDL.h"
#include "Globals.h"
#include "Engine.h"
#include "Healthbar.h"

class Entity {
public:
	Entity();
	Entity(int st_tileCol, int st_tileRow, int health);
	~Entity();

	SDL_Texture* m_texture;
	SDL_Rect m_rect;

	std::pair<int, int> m_curTile;
	int2 grid2dCoords;

	int m_healthLeft;

	Healthbar m_healthbar;

	void draw(SDL_Renderer* renderer);
	void moveToTile(int tileCol, int tileRow);
	void setCenterCoords(int2 centerCoords);
};