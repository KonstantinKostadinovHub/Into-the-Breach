#pragma once

#include <vector>
#include <string>
using namespace std;

class EntityAssets {
public:
	EntityAssets();
	~EntityAssets();

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