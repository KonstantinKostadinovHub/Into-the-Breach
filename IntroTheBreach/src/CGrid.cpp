#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

using std::ifstream;
using std::cout;

#include "Globals.h"
#include "Engine.h"
#include "CGrid.h"

CGrid::CGrid() {
	m_mainRenderer = nullptr;

	m_tileTextureFiles = "";
	m_tileShadowTextureFile = "";

	m_tileShadowTexture = nullptr;

	lastSelectedTile = { -1, -1 };
	selectedTile = false;
}

CGrid::~CGrid() {

}

void CGrid::init(SDL_Renderer* renderer) {
	m_mainRenderer = renderer;

	string label;

	ifstream fin;
	fin.open("config\\game\\grid_data.txt");

	fin >> label;

	string str_biomes;
	std::getline(fin, str_biomes);

	std::stringstream biomeStream(str_biomes);

	string currBiome;

	while (true) {
		biomeStream >> currBiome;

		if (!biomeStream.fail()) {
			biomes.push_back(currBiome);
		}
		else {
			break;
		}
	}


	fin >> label >> m_tileTextureFiles >> label;

	fin >> label >> m_tileShadowTextureFile;
	
	fin.close();

	//for (int i = 0; i < (int)biomes.size(); i++) {
	//	std::cout << biomes[i] << " ";
	//}
	//cout << '\n';

	int index = rand() % (int)biomes.size();


	fin.open("config\\game\\terrain\\" + biomes[index] + "\\count.txt");
	
	for (int i = 0; i < TERRAIN_OBJECTS; i++) {
		fin >> terrainObjectsCnt[i];

		cout << terrainObjectsCnt[i] << " ";
	}

	fin.close();

	for (int i = 0; i < terrainObjectsCnt[0]; i++) {
		m_tileTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\tile" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[1]; i++) {
		m_tileFluidTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\fluid" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[2]; i++) {
		m_mountainTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\mountain" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[3]; i++) {
		m_treeTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\tree" + intToStr(i + 1) + ".bmp"));
	}
	//m_tileTexture = loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\tile1.bmp");
	//m_tileFluidTexture = loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\fluid1.bmp");
	//m_mountainTexture = loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\mountain1.bmp");
	//m_tree1Texture = loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\tree1.bmp");
	//m_tree2Texture = loadTexture(m_mainRenderer, m_tileTextureFiles + biomes[index] + "\\tree2.bmp");

	m_tileShadowTexture = loadTexture(m_mainRenderer, m_tileShadowTextureFile);

	if (align_with == 'w') {
		m_tileSize = SCREEN_W / M_SIZE / 2.4;
	}
	else if (align_with == 'h') {
		m_tileSize = SCREEN_H / M_SIZE / 1.2;
	}

	CTile::m_gridSize = M_SIZE;

	giveTileSize(m_tileSize, m_tileSize * 2, m_tileSize * 2, M_SIZE);

	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			int indexTile = rand() % (int)m_tileTexture.size();

			tile[xx][yy].init(m_mainRenderer, m_tileTexture[indexTile], m_tileShadowTexture, { xx * m_tileSize, yy * m_tileSize }, m_tileSize, false, &terrain[xx][yy]);
			

			int indexTerrainType = rand() % 8;

			if (indexTerrainType == 0) {
				int indexMountainType = rand() % (int)m_mountainTexture.size();
				terrain[xx][yy].init(m_mainRenderer, m_mountainTexture[indexMountainType], "", { m_tileSize * 2, m_tileSize * 2 });
			}
			if (indexTerrainType == 1) {
				int indexTreeType = rand() % (int)m_treeTexture.size();
				terrain[xx][yy].init(m_mainRenderer, m_treeTexture[indexTreeType], "", { m_tileSize * 2, m_tileSize * 2 });
			}

			terrain[xx][yy].giveCentralPoint({ tile[xx][yy].m_isomRect.x + tile[xx][yy].m_isomRect.w / 2,
				tile[xx][yy].m_isomRect.y + tile[xx][yy].m_isomRect.h / 2 });
		}
	}
}

void CGrid::checkForOtherSelectedTiles(int2 CurrSelectedTileCoord) {
	if (tile[CurrSelectedTileCoord.x][CurrSelectedTileCoord.y].selected && 
		(CurrSelectedTileCoord.x != lastSelectedTile.x || CurrSelectedTileCoord.y != lastSelectedTile.y)) {

		if (selectedTile) {
			tile[lastSelectedTile.x][lastSelectedTile.y].selected = false;
		}
		selectedTile = true;

		lastSelectedTile.x = CurrSelectedTileCoord.x;
		lastSelectedTile.y = CurrSelectedTileCoord.y;
	}
}

void CGrid::update() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			tile[xx][yy].update();

			checkForOtherSelectedTiles({ xx, yy });

			terrain[xx][yy].update();
		}
	}
}

void CGrid::draw() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			tile[xx][yy].draw();

			terrain[xx][yy].draw();
		}
	}
}

void CGrid::quit() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			tile[xx][yy].quit();
			
			terrain[xx][yy].quit();
		}
	}

	for (int i = 0; i < (int)m_tileTexture.size(); i++) {
		SDL_DestroyTexture(m_tileTexture[0]);
		m_tileTexture.erase(m_tileTexture.begin());
	}
	for (int i = 0; i < (int)m_tileFluidTexture.size(); i++) {
		SDL_DestroyTexture(m_tileFluidTexture[0]);
		m_tileFluidTexture.erase(m_tileFluidTexture.begin());
	}
	for (int i = 0; i < (int)m_mountainTexture.size(); i++) {
		SDL_DestroyTexture(m_mountainTexture[0]);
		m_mountainTexture.erase(m_mountainTexture.begin());
	}
	for (int i = 0; i < (int)m_treeTexture.size(); i++) {
		SDL_DestroyTexture(m_treeTexture[0]);
		m_treeTexture.erase(m_treeTexture.begin());
	}
}

