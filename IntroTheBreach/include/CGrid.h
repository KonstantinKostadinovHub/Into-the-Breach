#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "CTile.h"
#include "CTerrain.h"
#include "Engine.h"
#include "CMap.h"

class CGrid {
public:
	CGrid();
	~CGrid();

	static const int M_SIZE = CMap::M_SIZE;
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

	CMap* m_currMap;

	CTile tile[M_SIZE][M_SIZE];
	CTerrain* terrain[M_SIZE][M_SIZE];

	int2 lastSelectedTile;
	bool selectedTile;

	void getBiomes();

	void makeTile(int2 slot);
	void makeTileFluid(int2 slot);

	void makeTerrainNone(int2 slot);
	void makeTerrainFluid(int2 slot);
	void makeTerrainMountain(int2 slot);
	void makeTerrainTree(int2 slot);

	void init(SDL_Renderer* renderer);
	void start(CMap* map);
	void checkForOtherSelectedTiles(int2 CurrSelectedTileCoord);
	void update();
	void draw();
	void quit();
};