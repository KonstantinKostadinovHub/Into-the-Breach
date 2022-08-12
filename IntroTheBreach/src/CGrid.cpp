#include <Windows.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

using std::ifstream;
using std::cout;

#include "Globals.h"
#include "Engine.h"
#include "CGrid.h"
#include "InputManger.h"
#include "CNoTerrain.h"
#include "CFluid.h"
#include "CMountain.h"
#include "CTree.h"

CGrid::CGrid() {
	m_mainRenderer = nullptr;

	m_tileTextureFiles = "";
	m_tileShadowTextureFile = "";

	m_tileShadowTexture = nullptr;

	m_lastSelectedTile = { -1, -1 };
	m_selectedTile = false;

	m_startCoords = { 0, 0 };
	m_distanceFromMouseToStart = { 0, 0 };
}

CGrid::~CGrid() {

}

void CGrid::getBiomes() {
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(L"img\\game\\terrain\\*", &data);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			m_biomes.push_back(wstrToStr(std::wstring(data.cFileName)));
		} while (FindNextFile(hFind, &data));

		FindClose(hFind);
	}

	for (int i = 0; i < (int)m_biomes.size(); i++) {
		if (m_biomes[i] == string(".") || m_biomes[i] == string("..")) {
			m_biomes.erase(m_biomes.begin() + i);
			i--;
		}
		else {
			std::cout << m_biomes[i] << '\n';
		}
	}
	cout << m_biomes.size() << '\n';
}


void CGrid::init(SDL_Renderer* renderer) {
	m_mainRenderer = renderer;

	getBiomes();

	string label;

	ifstream fin;

	fin.open("config\\game\\grid_data.txt");

	fin >> label >> m_tileTextureFiles >> label;
	fin >> label >> m_tileShadowTextureFile;
	
	fin.close();

	m_tileShadowTexture = loadTexture(m_mainRenderer, m_tileShadowTextureFile);

	if (align_with == 'w') {
		m_tileSize = SCREEN_W / 19;

		m_lengthToEdge = SCREEN_W / 30;
	}
	else if (align_with == 'h') {
		m_tileSize = SCREEN_H / 9.5;

		m_lengthToEdge = SCREEN_H / 15;
	}

	CTile::m_gridSize = M_SIZE;

	giveTileSize(m_tileSize, m_tileSize * 2, m_tileSize * 2, M_SIZE);

	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			m_tile[xx][yy] = new CTile();
			m_tile[xx][yy]->init(m_mainRenderer, nullptr, nullptr,
				{ xx * m_tileSize, yy * m_tileSize }, m_tileSize, false, nullptr); 
			// do not call CTile::update() or CTile::draw() before calling CGrid::start() or it will crash 
			// (because the pointer to terrain is nullptr)
		}
	}

	m_rect.w = m_tile[0][0]->m_isomRect.w * M_SIZE;
	m_rect.h = m_tile[0][0]->m_isomRect.h / 2 * (M_SIZE + 1);

	m_rect.x = m_tile[0][M_SIZE - 1]->m_isomRect.x;
	m_rect.y = m_tile[0][0]->m_isomRect.y;

	m_startCoords.x = gridToScreenCoords({ 0, 0 }).x;
	m_startCoords.y = gridToScreenCoords({ 0, 0 }).y;
}


void CGrid::makeTile(int2 slot) {
	int indexTile = rand() % (int)m_tileTexture.size();

	m_tile[slot.x][slot.y]->init(m_mainRenderer, m_tileTexture[indexTile], m_tileShadowTexture, 
		{ slot.x * m_tileSize, slot.y * m_tileSize }, m_tileSize, false, m_terrain[slot.x][slot.y]);
}

void CGrid::makeTileFluid(int2 slot) {
	int indexFluid = rand() % (int)m_tileFluidTexture.size();

	m_tile[slot.x][slot.y]->init(m_mainRenderer, m_tileFluidTexture[indexFluid], m_tileShadowTexture, 
		{ slot.x * m_tileSize, slot.y * m_tileSize }, m_tileSize, true, m_terrain[slot.x][slot.y]);
}

void CGrid::makeTerrainNone(int2 slot) {
	CNoTerrain* tmp_none = new CNoTerrain();

	m_terrain[slot.x][slot.y] = tmp_none;
}

void CGrid::makeTerrainFluid(int2 slot) {
	CFluid* tmp_fluid = new CFluid();
	tmp_fluid->init(m_mainRenderer, nullptr, { m_tileSize * 2, m_tileSize * 2 });

	m_terrain[slot.x][slot.y] = tmp_fluid;
}

void CGrid::makeTerrainMountain(int2 slot) {
	int indexMountainType = rand() % (int)m_mountainTexture.size();

	CMountain* tmp_mountain = new CMountain();
	tmp_mountain->init(m_mainRenderer, m_mountainTexture[indexMountainType], { m_tileSize * 2, m_tileSize * 2 });

	m_terrain[slot.x][slot.y] = tmp_mountain;
}

void CGrid::makeTerrainTree(int2 slot) {
	int indexTree = rand() % (int)m_treeTexture.size();

	CTree* tmp_tree = new CTree();
	tmp_tree->init(m_mainRenderer, m_treeTexture[indexTree], { m_tileSize * 2, m_tileSize * 2 });

	m_terrain[slot.x][slot.y] = tmp_tree;
}

void CGrid::makePowerhouse(int2 slot, POWERHOUSE type) {
	Powerhouse* ph = new Powerhouse();

	ph->init(m_mainRenderer, type, 1);

	m_tile[slot.x][slot.y]->addPowerhouse(ph);
}

void CGrid::getTextures(string biome) {
	int terrainObjectsCnt[4];

	ifstream fin;

	fin.open("config\\game\\terrain\\" + biome + "\\count.txt");

	for (int i = 0; i < TERRAIN_OBJECTS; i++) {
		fin >> terrainObjectsCnt[i];
	}

	fin.close();


	for (int i = 0; i < terrainObjectsCnt[0]; i++) {
		m_tileTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biome + "\\tile" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[1]; i++) {
		m_tileFluidTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biome + "\\fluid" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[2]; i++) {
		m_mountainTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biome + "\\mountain" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[3]; i++) {
		m_treeTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + biome + "\\tree" + intToStr(i + 1) + ".bmp"));
	}
}

void CGrid::loadTiles() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			if (m_currMap->m_map[xx][yy] == CMap::TILE) {
				makeTerrainNone({ xx, yy });

				makeTile({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == CMap::FLUID) {
				makeTerrainFluid({ xx, yy });

				makeTileFluid({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == CMap::MOUNTAIN) {
				makeTerrainMountain({ xx, yy });

				makeTile({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == CMap::TREE) {
				makeTerrainTree({ xx, yy });

				makeTile({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == CMap::PHOUSE1) {
				makeTerrainNone({ xx, yy });

				makeTile({ xx, yy });

				makePowerhouse({ xx, yy }, POWERHOUSE::SMALL);
			}
			else if (m_currMap->m_map[xx][yy] == CMap::PHOUSE2) {
				makeTerrainNone({ xx, yy });

				makeTile({ xx, yy });

				makePowerhouse({ xx, yy }, POWERHOUSE::MID);
			}
			else if (m_currMap->m_map[xx][yy] == CMap::PHOUSE3) {
				makeTerrainNone({ xx, yy });

				makeTile({ xx, yy });

				makePowerhouse({ xx, yy }, POWERHOUSE::LARGE);
			}
			else {
				int indexTerrainType = rand() % 11;

				if (indexTerrainType == 0) {
					makeTerrainFluid({ xx, yy });
				}
				else if (indexTerrainType == 1) {
					makeTerrainMountain({ xx, yy });
				}
				else if (indexTerrainType == 2) {
					makeTerrainTree({ xx, yy });
				}
				else {
					makeTerrainNone({ xx, yy });
				}

				if (indexTerrainType == 0) {
					makeTileFluid({ xx, yy });
				}
				else {
					makeTile({ xx, yy });
				}
			}

			cout << m_terrain[xx][yy]->getType() << "   ";
		}
		cout << '\n';
	}
}

void CGrid::start(CMap* map) {
	m_currMap = map;

	string currBiome;

	if (m_currMap->m_biome == "0") {
		int index = rand() % (int)m_biomes.size();
		currBiome = m_biomes[index];
	}
	else {
		currBiome = m_currMap->m_biome;
	}

	getTextures(currBiome);
	loadTiles();
}


void CGrid::checkForMovement() {
	if (InputManager::m_mouseCoord.x < 0 + m_lengthToEdge && InputManager::m_mouseCoord.x >= 0) {
		if (m_startCoords.x <= m_rect.w / 2) {
			m_startCoords.x += m_lengthToEdge / 6;
		}
	}
	if (InputManager::m_mouseCoord.x > SCREEN_W - m_lengthToEdge && InputManager::m_mouseCoord.x <= SCREEN_W) {
		if (m_startCoords.x >= SCREEN_W - m_rect.w / 2) {
			m_startCoords.x -= m_lengthToEdge / 6;
		}
	}
	if (InputManager::m_mouseCoord.y < 0 + m_lengthToEdge && InputManager::m_mouseCoord.y >= 0) {
		if (m_startCoords.y <= m_tile[0][0]->m_isomRect.h / 2) {
			m_startCoords.y += m_lengthToEdge / 6;
		}
	}
	if (InputManager::m_mouseCoord.y > SCREEN_H - m_lengthToEdge && InputManager::m_mouseCoord.y <= SCREEN_H) {
		if (m_startCoords.y >= SCREEN_H - m_rect.h) {
			m_startCoords.y -= m_lengthToEdge / 6;
		}
	}
}


void CGrid::checkForOtherSelectedTiles(int2 CurrSelectedTileCoord) {
	if (m_tile[CurrSelectedTileCoord.x][CurrSelectedTileCoord.y]->selected && 
		(CurrSelectedTileCoord.x != m_lastSelectedTile.x || CurrSelectedTileCoord.y != m_lastSelectedTile.y)) {

		if (m_selectedTile) {
			m_tile[m_lastSelectedTile.x][m_lastSelectedTile.y]->selected = false;
		}
		m_selectedTile = true;

		m_lastSelectedTile.x = CurrSelectedTileCoord.x;
		m_lastSelectedTile.y = CurrSelectedTileCoord.y;
	}
}

void CGrid::update() {
	checkForMovement();

	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			m_tile[xx][yy]->setGridCoords(int2(screenToGridCoords(m_startCoords).x + xx * m_tileSize, screenToGridCoords(m_startCoords).y + yy * m_tileSize));
			m_tile[xx][yy]->update();

			checkForOtherSelectedTiles({ xx, yy });

			//terrain[xx][yy]->update();
		}
	}
}

void CGrid::draw() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			m_tile[xx][yy]->draw();

			//terrain[xx][yy]->draw();
		}
	}
}

void CGrid::quit() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			m_tile[xx][yy]->quit();
			delete m_tile[xx][yy];
			
			m_terrain[xx][yy]->quit();
			delete m_terrain[xx][yy];
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

