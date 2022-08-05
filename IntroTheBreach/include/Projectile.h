#pragma once

#include "SDL.h"
#include "Globals.h"
#include "Engine.h"

class Projectile {
public:
	Projectile();
	Projectile(int st_tileCol, int st_tileRow, int destinationTileCol, int destinationTileRow);
	~Projectile();

	SDL_Texture* m_texture;
	SDL_Rect m_rect; //Isometric coords

	float3 m_vel;
	int2 m_realCoords;
	int2 m_destinationCoords;
	float m_z;

	bool m_delete;

	void draw(SDL_Renderer* renderer);
	void update();
};