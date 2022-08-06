#pragma once

#include <vector>
#include "SDL.h"
#include "Globals.h"
#include "Engine.h"
#include "Projectile.h"
#include "Healthbar.h"
using std::pair;

class Entity {
public:
	Entity();
	Entity(int st_tileCol, int st_tileRow, int health);
	~Entity();

	SDL_Texture* m_texture;
	SDL_Rect m_rect; //Isometric coords

	pair<int, int> m_curTile;
	pair<int, int> m_destinationTile;
	float2 grid2dCoords;

	std::vector<Projectile> m_projectile;
	Healthbar m_healthbar;

	int m_healthLeft;

	bool m_moving;
	float2 m_moveSpeed;


	void draw(SDL_Renderer* renderer);
	void update();
	void moveToTile(int tileCol, int tileRow);
	void continueMoving();
	void attack(int attackedTileCol, int attackedTileRow);
	void setCoordsOnTile(int tileCol, int tileRow);
	void setCenterCoords(int2 centerCoords);
	void setBottomCenterCoords(int2 bottomCenterCoords);
};