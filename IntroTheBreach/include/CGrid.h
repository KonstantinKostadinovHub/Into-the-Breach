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

	string m_shadowTextureFile;
	SDL_Texture* m_shadowTexture;

	int m_tileSize;

	CTile tile[m_size][m_size];

	int2 lastSelectedTile;
	bool selectedTile;

	void init(SDL_Renderer* renderer);
	void checkForOtherSelectedTiles(int2 CurrSelectedTileCoord);
	void update();
	void draw();
	void quit();
};