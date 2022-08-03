#pragma once

#include <SDL.h>
#include <string>

using std::string;

#include "CTile.h"

class CGrid {
public:
	CGrid();
	~CGrid();

	static const int m_size = 8;

	SDL_Renderer* m_mainRenderer;

	string m_tileTextureFile;
	SDL_Texture* m_tileTexture;

	int m_tileSize;

	CTile tile[m_size][m_size];

	void init(SDL_Renderer* renderer);
	void update();
	void draw();
	void quit();
};