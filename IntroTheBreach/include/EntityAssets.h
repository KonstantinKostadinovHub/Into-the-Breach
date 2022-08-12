#pragma once

#include "SDL.h"
#include <vector>
#include <string>
using namespace std;

class EntityAssets {
public:
	EntityAssets();
	~EntityAssets();

	SDL_Texture* m_texture;

	std::string m_name;
	int m_health;
	int m_moveRadius;

	bool m_ranged;

	bool m_jumpingMelee;
	
	bool m_straightProjectile;
	bool m_piercingProjectile;
	bool m_doKnockback;

	vector<pair<int, int>> m_movableTiles;
};