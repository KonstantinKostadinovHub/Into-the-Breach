#include <fstream>

using std::ifstream;

#include "Globals.h"
#include "CGrid.h"

CGrid::CGrid() {
	m_mainRenderer = nullptr;

	m_tileTextureFile = "";
	m_tileTexture = nullptr;

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

	fin >> m_tileTextureFile >> m_tileTextureFile;
	fin >> m_shadowTextureFile >> m_shadowTextureFile;

	fin.close();

	m_tileTexture = loadTexture(m_mainRenderer, m_tileTextureFile);
	m_shadowTexture = loadTexture(m_mainRenderer, m_shadowTextureFile);

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
			tile[xx][yy].init(m_mainRenderer, m_tileTexture, m_shadowTexture, { xx * m_tileSize, yy * m_tileSize }, m_tileSize);
		}
	}
}

void CGrid::update() {
	for (int yy = 0; yy < m_size; yy++) {
		for (int xx = 0; xx < m_size; xx++) {
			tile[xx][yy].update();

			if (tile[xx][yy].selected && (xx != lastSelectedTile.x || yy != lastSelectedTile.y)) {
				if (selectedTile) {
					tile[lastSelectedTile.x][lastSelectedTile.y].selected = false;
				}
				selectedTile = true;

				lastSelectedTile.x = xx;
				lastSelectedTile.y = yy;
			}
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

}
