#include <fstream>

using std::ifstream;

#include "CGame.h"
#include "Engine.h"
#include "Globals.h"

CGame::CGame() {
	m_mainRenderer = nullptr;

	m_bgrTextureFile = "";
	m_bgrTextureOverlayFile = "";

	m_bgrRect = { 0, 0, 1, 1 };
	m_bgrTexture = nullptr;
	m_bgrTextureOverlay = nullptr;
}

CGame::~CGame() {

}

void CGame::loadMap(int lvl) {
	ifstream fin;
	fin.open("levels\\" + intToStr(lvl) + ".lvl");

	fin >> m_currMap.m_biome;

	for (int yy = 0; yy < CMap::M_SIZE; yy++) {
		for (int xx = 0; xx < CMap::M_SIZE; xx++) {
			fin >> m_currMap.m_map[xx][yy];
		}
	}

	fin.close();

	m_currMap.init();
}

void CGame::init(SDL_Renderer* renderer) {
	m_mainRenderer = renderer;

	ifstream fin;
	fin.open("config\\game\\data.txt");

	fin >> m_bgrTextureFile >> m_bgrTextureFile;
	fin >> m_bgrTextureOverlayFile >> m_bgrTextureOverlayFile;

	fin.close();

	m_bgrTexture = loadTexture(m_mainRenderer, m_bgrTextureFile);
	m_bgrTextureOverlay = loadTexture(m_mainRenderer, m_bgrTextureOverlayFile);

	if (align_with == 'w')
	{
		m_bgrRect.w = SCREEN_W;
		m_bgrRect.h = SCREEN_W * 576 / 1024;

		m_bgrRect.x = 0;
		m_bgrRect.y = (SCREEN_H - m_bgrRect.h) / 2;
	}
	else if (align_with == 'h')
	{
		m_bgrRect.h = SCREEN_H;
		m_bgrRect.w = SCREEN_H * 1024 / 576;

		m_bgrRect.y = 0;
		m_bgrRect.x = (SCREEN_W - m_bgrRect.w) / 2;
	}

	loadMap(0);

	m_grid.init(m_mainRenderer);
	m_grid.start(&m_currMap);
}

void CGame::update() {
	m_grid.update();
}

void CGame::draw() {
	SDL_RenderCopy(m_mainRenderer, m_bgrTexture, NULL, &m_bgrRect);
	SDL_RenderCopy(m_mainRenderer, m_bgrTextureOverlay, NULL, &m_bgrRect);
	m_grid.draw();
}

void CGame::quit() {
	m_grid.quit();

	SDL_DestroyTexture(m_bgrTexture);
	SDL_DestroyTexture(m_bgrTextureOverlay);
}
