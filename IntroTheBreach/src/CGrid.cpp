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
#include "CNoTerrain.h"
#include "CFluid.h"
#include "CMountain.h"
#include "CTree.h"

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

void CGrid::getBiomes() {
	vector <std::string> v;

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(L"img\\game\\terrain\\*", &data);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(wstrToStr(std::wstring(data.cFileName)));
		} while (FindNextFile(hFind, &data));

		FindClose(hFind);
	}

	for (int i = 0; i < v.size(); i++) {
		if (v[i] == string(".") || v[i] == string("..")) {
			v.erase(v.begin() + i);
			i--;
		}
		else {
			std::cout << v[i] << '\n';
		}
	}
	cout << v.size() << '\n';
}


void CGrid::init(SDL_Renderer* renderer) {
	getBiomes();
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

	m_tileShadowTexture = loadTexture(m_mainRenderer, m_tileShadowTextureFile);

	if (align_with == 'w') {
		m_tileSize = SCREEN_W / M_SIZE / 2.4;
	}
	else if (align_with == 'h') {
		m_tileSize = SCREEN_H / M_SIZE / 1.2;
	}

	CTile::m_gridSize = M_SIZE;

	giveTileSize(m_tileSize, m_tileSize * 2, m_tileSize * 2, M_SIZE);
}


void CGrid::makeTile(int2 slot) {
	int indexTile = rand() % (int)m_tileTexture.size();

	tile[slot.x][slot.y].init(m_mainRenderer, m_tileTexture[indexTile], m_tileShadowTexture, { slot.x * m_tileSize, slot.y * m_tileSize }, m_tileSize, false, terrain[slot.x][slot.y]);
}

void CGrid::makeTileFluid(int2 slot) {
	int indexFluid = rand() % (int)m_tileFluidTexture.size();

	tile[slot.x][slot.y].init(m_mainRenderer, m_tileFluidTexture[indexFluid], m_tileShadowTexture, { slot.x * m_tileSize, slot.y * m_tileSize }, m_tileSize, true, terrain[slot.x][slot.y]);
}

void CGrid::makeTerrainNone(int2 slot) {
	CNoTerrain* tmp_none = new CNoTerrain();

	terrain[slot.x][slot.y] = tmp_none;
}

void CGrid::makeTerrainFluid(int2 slot) {
	CFluid* tmp_fluid = new CFluid();
	tmp_fluid->init(m_mainRenderer, nullptr, { m_tileSize * 2, m_tileSize * 2 });

	terrain[slot.x][slot.y] = tmp_fluid;
}

void CGrid::makeTerrainMountain(int2 slot) {
	int indexMountainType = rand() % (int)m_mountainTexture.size();

	CMountain* tmp_mountain = new CMountain();
	tmp_mountain->init(m_mainRenderer, m_mountainTexture[indexMountainType], { m_tileSize * 2, m_tileSize * 2 });

	terrain[slot.x][slot.y] = tmp_mountain;
}

void CGrid::makeTerrainTree(int2 slot) {
	int indexTree = rand() % (int)m_treeTexture.size();

	CTree* tmp_tree = new CTree();
	tmp_tree->init(m_mainRenderer, m_treeTexture[indexTree], { m_tileSize * 2, m_tileSize * 2 });

	terrain[slot.x][slot.y] = tmp_tree;
}

void CGrid::loadPowerhouses(int lvl)
{
	int s, m, l;

	// read from file
	ifstream stream;
	stream.open("levels\\powerhouses_" + std::to_string(lvl) + ".lvl");

	stream >> s >> m >> l;

	stream.close();

	// generate randomly
	makePowerhouseBySize(POWERHOUSE::SMALL, s);
	makePowerhouseBySize(POWERHOUSE::MID, m);
	makePowerhouseBySize(POWERHOUSE::LARGE, l);
}

void CGrid::makePowerhouseBySize(POWERHOUSE type, int quantity)
{
	while (quantity > 0)
	{

		int x = rand() % CMap::M_SIZE;
		int y = rand() % CMap::M_SIZE;

		cout << quantity << " " << x << " " << y << '\n';

		Powerhouse* ph = new Powerhouse();

		ph->init(m_mainRenderer, POWERHOUSE::SMALL, 1);

		if (tile[x][y].addPowerhouse(ph))
		{
			quantity--;
		}
		else
		{
			ph->destroy();
			delete ph;
		}
	}
}

void CGrid::start(CMap* map) {
	m_currMap = map;

	ifstream fin;

	string currBiome;

	if (m_currMap->m_biome == "0") {
		int index = rand() % (int)biomes.size();
		currBiome = biomes[index];
	}
	else {
		currBiome = m_currMap->m_biome;
	}

	fin.open("config\\game\\terrain\\" + currBiome + "\\count.txt");
	
	for (int i = 0; i < TERRAIN_OBJECTS; i++) {
		fin >> terrainObjectsCnt[i];
	}

	fin.close();


	for (int i = 0; i < terrainObjectsCnt[0]; i++) {
		m_tileTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + currBiome + "\\tile" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[1]; i++) {
		m_tileFluidTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + currBiome + "\\fluid" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[2]; i++) {
		m_mountainTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + currBiome + "\\mountain" + intToStr(i + 1) + ".bmp"));
	}
	for (int i = 0; i < terrainObjectsCnt[3]; i++) {
		m_treeTexture.push_back(loadTexture(m_mainRenderer, m_tileTextureFiles + currBiome + "\\tree" + intToStr(i + 1) + ".bmp"));
	}

	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			if (m_currMap->m_map[xx][yy] == '0') {
				makeTerrainNone({ xx, yy });

				makeTile({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == 'W') {
				makeTerrainFluid({ xx, yy });

				makeTileFluid({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == 'M') {
				makeTerrainMountain({ xx, yy });
				
				makeTile({ xx, yy });
			}
			else if (m_currMap->m_map[xx][yy] == 'T') {
				makeTerrainTree({ xx, yy });

				makeTile({ xx, yy });
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

			//terrain[xx][yy]->giveCentralPoint({ tile[xx][yy].m_isomRect.x + tile[xx][yy].m_isomRect.w / 2,
			//		tile[xx][yy].m_isomRect.y + tile[xx][yy].m_isomRect.h / 2 });

			cout << terrain[xx][yy]->getType() << "   ";
		}
		cout << '\n';
	}

	loadPowerhouses(0);
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

			//std::cout << "asd\n";
			terrain[xx][yy]->update();
			//std::cout << "aaaaaaaaaaasssdddddddddd\n";
		}
	}
}

void CGrid::draw() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			tile[xx][yy].draw();

			terrain[xx][yy]->draw();
		}
	}
}

void CGrid::quit() {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			tile[xx][yy].quit();
			
			terrain[xx][yy]->quit();
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

