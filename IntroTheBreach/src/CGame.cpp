#include <fstream>

using std::ifstream;

#include "CGame.h"
#include "Engine.h"
#include "Globals.h"

CGame::CGame() {
	m_mainRenderer = nullptr;

	m_bgrTextureFile = "";
	m_bgrTextureOverlayFile = "";

	m_bgrRect = SDL_Rect();
	m_bgrTexture = nullptr;
	m_bgrTextureOverlay = nullptr;
}

CGame::~CGame() {

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
}

void CGame::update() {

}

void CGame::draw() {
	SDL_RenderCopy(m_mainRenderer, m_bgrTexture, NULL, &m_bgrRect);
	SDL_RenderCopy(m_mainRenderer, m_bgrTextureOverlay, NULL, &m_bgrRect);
}

void CGame::quit() {
	SDL_DestroyTexture(m_bgrTexture);
	SDL_DestroyTexture(m_bgrTextureOverlay);
}
