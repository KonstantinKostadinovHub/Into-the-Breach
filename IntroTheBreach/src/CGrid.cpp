#include <fstream>
#include <ctime>

using std::ifstream;

#include "Globals.h"
#include "CGrid.h"

CGrid::CGrid() {
	m_mainRenderer = nullptr;

	m_tileDirtTextureFile = "";
	m_tileDirtTexture = nullptr;

	m_tileSandTextureFile = "";
	m_tileSandTexture = nullptr;

	m_tileOverlayTextureFile = "";
	m_tileOverlayTexture = nullptr;

	m_shadowTextureFile = "";
	m_shadowTexture = nullptr;

	lastSelectedTile = { -1, -1 };
	selectedTile = false;
}

CGrid::~CGrid() {

}

void CGrid::init(SDL_Renderer* renderer) {
	m_mainRenderer = renderer;

	ifstream fin;
	fin.open("config\\game\\grid_data.txt");

	fin >> m_tileDirtTextureFile >> m_tileDirtTextureFile;
	fin >> m_tileSandTextureFile >> m_tileSandTextureFile;
	fin >> m_tileOverlayTextureFile >> m_tileOverlayTextureFile;
	fin >> m_shadowTextureFile >> m_shadowTextureFile;

	int3 curr_color;
	string label;

	fin >> label >> curr_color.x >> curr_color.y >> curr_color.z;
	m_grassColor.push_back(curr_color);

	fin >> label >> curr_color.x >> curr_color.y >> curr_color.z;
	m_grassColor.push_back(curr_color);

	fin >> label >> curr_color.x >> curr_color.y >> curr_color.z;
	m_grassColor.push_back(curr_color);

	fin >> label >> curr_color.x >> curr_color.y >> curr_color.z;
	m_grassColor.push_back(curr_color);

	m_grassColor.push_back({ 255, 255, 255 });
	m_grassColor.push_back({ 255, 255, 255 });

	fin.close();

	m_tileDirtTexture = loadTexture(m_mainRenderer, m_tileDirtTextureFile);
	m_tileSandTexture = loadTexture(m_mainRenderer, m_tileSandTextureFile);
	m_tileOverlayTexture = loadTexture(m_mainRenderer, m_tileOverlayTextureFile);
	m_shadowTexture = loadTexture(m_mainRenderer, m_shadowTextureFile);

	m_tileTexture.push_back({ m_tileDirtTexture, m_tileOverlayTexture });
	m_tileTexture.push_back({ m_tileDirtTexture, m_tileOverlayTexture });
	m_tileTexture.push_back({ m_tileDirtTexture, m_tileOverlayTexture });
	m_tileTexture.push_back({ m_tileDirtTexture, m_tileOverlayTexture });
	m_tileTexture.push_back({ m_tileDirtTexture, nullptr });
	m_tileTexture.push_back({ m_tileSandTexture, nullptr });

	int index = rand() % (int)m_tileTexture.size();
	SDL_SetTextureColorMod(m_tileTexture[index].overlay, m_grassColor[index].x, m_grassColor[index].y, m_grassColor[index].z);

	if (align_with == 'w') {
		m_tileSize = SCREEN_W / m_size / 2.4;
	}
	else if (align_with == 'h') {
		m_tileSize = SCREEN_H / m_size / 1.2;
	}

	CTile::m_gridSize = m_size;

	giveTileSize(m_tileSize, m_tileSize * 2, m_tileSize * 2, m_size);

	for (int yy = 0; yy < m_size; yy++) {
		for (int xx = 0; xx < m_size; xx++) {
			tile[xx][yy].init(m_mainRenderer, m_tileTexture[index].texture, m_tileTexture[index].overlay, m_shadowTexture, {xx * m_tileSize, yy * m_tileSize}, m_tileSize);
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
	for (int yy = 0; yy < m_size; yy++) {
		for (int xx = 0; xx < m_size; xx++) {
			tile[xx][yy].update();

			checkForOtherSelectedTiles({ xx, yy });
		}
	}
}

void CGrid::draw() {
	for (int yy = 0; yy < m_size; yy++) {
		for (int xx = 0; xx < m_size; xx++) {
			tile[xx][yy].draw();
		}
	}
}

void CGrid::quit() {
	for (int yy = 0; yy < m_size; yy++) {
		for (int xx = 0; xx < m_size; xx++) {
			tile[xx][yy].quit();
		}
	}

	SDL_DestroyTexture(m_tileDirtTexture);
	SDL_DestroyTexture(m_shadowTexture);
}

