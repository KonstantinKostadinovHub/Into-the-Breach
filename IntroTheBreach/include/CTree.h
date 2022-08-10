#pragma once

#include "CTerrain.h"

class CTree : public CTerrain {
public:
	CTree();
	~CTree();

	static string m_type;
	static int m_maxHealth;

	string getType();

	void init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size);
	//void update();
	void draw();
	void quit();
};