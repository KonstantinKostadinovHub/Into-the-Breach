#pragma once

#include "Globals.h"
#include "Engine.h"
#include <vector>

using std::vector;

enum class POWERHOUSE
{
	NONE = 0,
	SMALL = 1,
	MID = 2,
	LARGE = 3
};

class Powerhouse
{
public:
	Powerhouse();
	~Powerhouse();

	void init(SDL_Renderer* renderer, POWERHOUSE type, int team);
	void destroy();

	void takeDamage(int damage);

	void draw(SDL_Renderer* renderer, int2 coor);

	static int getTeamHealth(int team);

private:
	int m_team;
	int m_health;
	SDL_Rect m_rect;
	SDL_Texture* m_texture;

	static vector<Powerhouse*> m_all;
};