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

	int2 m_startCoords;
	int2 m_distanceFromMouseToStart;

	int m_lengthToEdge;

	SDL_Rect m_rect;
	int2 distToScreen;

	static const int M_SIZE = CMap::M_SIZE;
	static const int TERRAIN_OBJECTS = 4;

	CMap* m_currMap;

	CTile* m_tile[M_SIZE][M_SIZE];
	CTerrain* m_terrain[M_SIZE][M_SIZE]; // each tile recieves a pointer to its respective terrain; it takes care for the draw and update
	Entity* m_entity[M_SIZE][M_SIZE];

	int m_tileSize;

	int2 m_lastSelectedTile;
	bool m_selectedTile;

	vector <string> m_biomes; // all file names in directory "img\\game\\terrain\\"

	SDL_Renderer* m_mainRenderer;

	string m_tileTextureFiles; // path to the directory with biomes ("img\\game\\terrain\\")
	string m_tileShadowTextureFile;

	vector <SDL_Texture*> m_tileTexture;
	vector <SDL_Texture*> m_tileFluidTexture;
	vector <SDL_Texture*> m_mountainTexture;
	vector <SDL_Texture*> m_treeTexture;

	SDL_Texture* m_tileShadowTexture;	

	void checkForMovement();

	void getBiomes();
	void getTextures(string biome);

	void makeEntity(int2 tile);

	void makeTile(int2 slot);
	void makeTileFluid(int2 slot);

	void makeTerrainNone(int2 slot);
	void makeTerrainFluid(int2 slot);
	void makeTerrainMountain(int2 slot);
	void makeTerrainTree(int2 slot);

	void makePowerhouse(int2 slot, POWERHOUSE type);

	void loadTiles();

	void loadPowerhouses(int lvl);
	void makePowerhouseBySize(POWERHOUSE type, int quantity);

	void init(SDL_Renderer* renderer);
	void start(CMap* map);

	void checkForOtherSelectedTiles(int2 CurrSelectedTileCoord);
	void update();

	void draw();
	void quit();
};