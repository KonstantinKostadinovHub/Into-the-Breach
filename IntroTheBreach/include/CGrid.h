#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "CTile.h"
#include "CTerrain.h"
#include "Engine.h"

class CGrid {
public:
	CGrid();
	~CGrid();

	static const int M_SIZE = 8;
	static const int TERRAIN_OBJECTS = 4;

	SDL_Renderer* m_mainRenderer;

	vector <string> biomes; // all file names in directory "img\\game\\terrain\\"

	string m_tileTextureFiles; // path to the directory with biomes ("img\\game\\terrain\\")
	string m_tileShadowTextureFile;

	int terrainObjectsCnt[TERRAIN_OBJECTS]; // the count of each object (1 tile, 1 fluid, 1 mountain, 2 trees)

	vector <SDL_Texture*> m_tileTexture;
	vector <SDL_Texture*> m_tileFluidTexture;
	vector <SDL_Texture*> m_mountainTexture;
	vector <SDL_Texture*> m_treeTexture;

	SDL_Texture* m_tileShadowTexture;

	int m_tileSize;

	CTile tile[M_SIZE][M_SIZE];
	CTerrain terrain[M_SIZE][M_SIZE];

	int2 lastSelectedTile;
	bool selectedTile;

	void init(SDL_Renderer* renderer);
	void checkForOtherSelectedTiles(int2 CurrSelectedTileCoord);
	void update();
	void draw();
	void quit();
};