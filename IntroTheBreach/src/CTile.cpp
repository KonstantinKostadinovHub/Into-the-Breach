#include "CTile.h"
#include "Globals.h"

#include <iostream>

int CTile::m_gridSize = 0;

CTile::CTile() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;

	m_button.m_rect = { 0, 0, 1, 1 };
	m_rectLifted = { 0, 0, 1, 1 };
	m_button.button_down = false;
	m_isomRect = { 0, 0, 1, 1 };
	m_isomRectLifted = { 0, 0, 1, 1 };

	hovered = false;

	z_add = 0;
}

CTile::~CTile() {

}

void CTile::init(SDL_Renderer* renderer, SDL_Texture* texture, int2 coord, int size) {
	m_mainRenderer = renderer;

	m_texture = texture;

	m_button.m_rect.w = size;
	m_button.m_rect.h = size;

	m_button.m_rect.x = coord.x;
	m_button.m_rect.y = coord.y;

	m_isomRect.w = m_button.m_rect.h / 2 * 4;// 1.732 * m_rect.h;
	m_isomRect.h = m_button.m_rect.h / 2 * 2 + m_button.m_rect.h;// size + m_rect.h;

	int2 tmp;
	tmp = gridToScreenCoords({ m_button.m_rect.x, m_button.m_rect.y });

	if (align_with == 'w') {
		z_add = SCREEN_W / 100;
	}
	else if (align_with == 'h') {
		z_add = SCREEN_H / 50;
	}

	m_isomRect.x = tmp.x;
	m_isomRect.y = tmp.y;

	int m_rectLift = 0;// z_add * 1.414;

	m_rectLifted = m_button.m_rect;
	m_rectLifted.x -= m_rectLift;
	m_rectLifted.y -= m_rectLift;

	m_isomRectLifted = m_isomRect;
	m_isomRectLifted.y -= z_add;
}

void CTile::update() {
	int2 tmp = screenToGridCoords(InputManager::m_mouseCoord);

	if (hovered) {
		if (!collidingRectAndPoint(m_rectLifted, tmp)) {
			hovered = false;
		}
	}
	else if (collidingRectAndPoint(m_button.m_rect, tmp)) {
		hovered = true;
	}
}

void CTile::draw() {
	if (hovered) {
		SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_isomRectLifted);
	}
	else {
		SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_isomRect);
	}

	//SDL_Rect tmp = { screenToGridCoords(InputManager::m_mouseCoord).x, screenToGridCoords(InputManager::m_mouseCoord).y, 5, 5 };

	//SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_button.m_rect);
	//SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &tmp);
}

void CTile::quit() {

}
