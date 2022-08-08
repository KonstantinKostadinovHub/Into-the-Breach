#pragma once

#include "CTerrain.h"

class CFluid : public CTerrain {
public:
	CFluid();
	~CFluid();

	static string m_type;
	static int m_maxHealth;

	string getType();

	void init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size);
	//void update();
	void draw();
	void quit();
};