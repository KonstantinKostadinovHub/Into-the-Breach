#include "CTile.h"
#include "Globals.h"

#include <iostream>

int CTile::m_gridSize = 0;

CTile::CTile() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;

	m_rect = { 0, 0, 1, 1 };
	m_isomRect = { 0, 0, 1, 1 };
}

CTile::~CTile() {

}

void CTile::init(SDL_Renderer* renderer, SDL_Texture* texture, int2 coord, int size) {
	m_mainRenderer = renderer;

	m_texture = texture;

	m_rect.w = size;
	m_rect.h = size;

	m_rect.x = coord.x;
	m_rect.y = coord.y;

	m_isomRect.w = m_rect.h / 2 * 4;// 1.732 * m_rect.h;
	m_isomRect.h = m_rect.h / 2 * 2 + m_rect.h;// size + m_rect.h;

	int2 tmp;
	tmp = gridToScreenCoords({ m_rect.x, m_rect.y });

	m_isomRect.x = tmp.x + SCREEN_W / 2 - m_isomRect.w / 2;
	m_isomRect.y = tmp.y + (SCREEN_H - m_isomRect.h / 2 * (m_gridSize + 1)) / 2;// -(m_rect.x / m_rect.w + m_rect.y / m_rect.h) * 4;
}

void CTile::update() {

}

void CTile::draw() {
	SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_isomRect);

	/*std::cout << m_mainRenderer << " " << m_texture << "\n"
		<< m_rect.x << " " << m_rect.y << " " << m_rect.w << " " << m_rect.h << "\n\n\n";*/
}

void CTile::quit() {

}
