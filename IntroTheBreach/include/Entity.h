#pragma once

#include <fstream>
#include <vector>
#include "SDL.h"
#include "Globals.h"
#include "Engine.h"
#include "EntityAssets.h"
#include "Projectile.h"
#include "Healthbar.h"
using std::pair;

class Entity {
public:
	Entity();
	Entity(int st_tileCol, int st_tileRow, int identity,  bool enemy);
	~Entity();

	static std::vector<EntityAssets> m_ENTITIES;

	SDL_Texture* m_texture;
	SDL_Rect m_rect; //Isometric coords

	pair<int, int> m_curTile;
	pair<int, int> m_destinationTile;
	float2 grid2dCoords;

	std::vector<Projectile> m_projectile;
	Healthbar m_healthbar;

	int m_type;
	bool m_enemy;

	bool m_dead;

	bool m_moving;
	float2 m_moveSpeed;

	void draw(SDL_Renderer* renderer);
	void update();
	
	static void readEntityAssets(SDL_Renderer* renderer);

	void moveToTile(int tileCol, int tileRow);
	void continueMoving();
	void attack(int attackedTileCol, int attackedTileRow);
	void decreaseHealth(int decrease);

	void setCoordsOnTile(int tileCol, int tileRow);
	void setCenterCoords(int2 centerCoords);
	void setBottomCenterCoords(int2 bottomCenterCoords);
};