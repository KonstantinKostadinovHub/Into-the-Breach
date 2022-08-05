#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "CTile.h"
#include "Engine.h"

class CGrid {
public:
	CGrid();
	~CGrid();

	static const int m_size = 8;

	SDL_Renderer* m_mainRenderer;

	string m_tileDirtTextureFile;
	SDL_Texture* m_tileDirtTexture;

	string m_tileSandTextureFile;
	SDL_Texture* m_tileSandTexture;

	string m_tileOverlayTextureFile;
	SDL_Texture* m_tileOverlayTexture;

	string m_shadowTextureFile;
	SDL_Texture* m_shadowTexture;

	vector <int3> m_grassColor;
	vector <SDL_Texture2> m_tileTexture;

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