#include "CTile.h"
#include "Globals.h"

#include <iostream>

int CTile::m_gridSize = 0;

CTile::CTile() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;
	m_shadowTexture = nullptr;
	m_powerhouse = nullptr;

	m_button.m_rect = { 0, 0, 1, 1 };
	m_rectLifted = { 0, 0, 1, 1 };
	m_button.button_down = false;
	m_isomRect = { 0, 0, 1, 1 };
	m_isomRectLifted = { 0, 0, 1, 1 };

	hovered = false;
	selected = false;

	water = false;

	z_add = 0;

	m_terrain = nullptr;
}

CTile::~CTile() {

}

void CTile::init(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* shadow_texture, int2 coord, int size, bool is_water, CTerrain* terrain) {
	m_mainRenderer = renderer;

	m_texture = texture;
	m_shadowTexture = shadow_texture;

	m_button.m_rect.w = size;
	m_button.m_rect.h = size;

	m_button.m_rect.x = coord.x;
	m_button.m_rect.y = coord.y;

	m_isomRect.w = m_button.m_rect.h / 2 * 4;// 1.732 * m_rect.h;
	m_isomRect.h = m_button.m_rect.h / 2 * 2 + m_button.m_rect.h;// size + m_rect.h;

	int2 tmp;
	tmp = gridToScreenCoords({ m_button.m_rect.x, m_button.m_rect.y });

	z_add = size / 5;

	m_isomRect.x = tmp.x - m_isomRect.w / 2;
	m_isomRect.y = tmp.y;

	int m_rectLift = 0;// z_add * 1.414;

	m_rectLifted = m_button.m_rect;
	m_rectLifted.x -= m_rectLift;
	m_rectLifted.y -= m_rectLift;

	m_isomRectLifted = m_isomRect;
	m_isomRectLifted.y -= z_add;

	water = is_water;

	m_terrain = terrain;

	m_powerhouse = nullptr;
}

/*
* @return - can we put a powerhouse on this tile
*/
bool  CTile::addPowerhouse(Powerhouse* powerhouse)
{
	if (m_powerhouse != nullptr || m_terrain->getType() == "fluid" || m_terrain->getType() == "mountain" || m_terrain->getType() == "tree")
	{
		return false;
	}

	m_powerhouse = powerhouse;

	return true;
}

void CTile::update() {
	if (water) {
		return;
	}
	int2 tmp = screenToGridCoords(InputManager::m_mouseCoord);

	if (hovered) {
		if (!collidingRectAndPoint(m_rectLifted, tmp)) {
			hovered = false;
		}
	}
	else if (collidingRectAndPoint(m_button.m_rect, tmp)) {
		hovered = true;
	}

	bool down = m_button.pressed(tmp);

	if (down && !selected) {
		selected = true;
	}
	else {
		if (down && selected) {
			selected = false;
		}
	}
}

void CTile::draw() {
	if (hovered || m_button.button_down || selected) {
		SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_isomRectLifted);

		m_terrain->giveCentralPoint({ m_isomRectLifted.x + m_isomRectLifted.w / 2 , m_isomRectLifted.y + m_isomRectLifted.h / 2 });
		if (m_powerhouse)
		{
			m_powerhouse->draw(m_mainRenderer, { m_isomRectLifted.x + m_isomRectLifted.w / 2 , m_isomRectLifted.y + m_isomRectLifted.h / 2 });
		}
	}
	else {
		SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_isomRect);

		m_terrain->giveCentralPoint({ m_isomRect.x + m_isomRect.w / 2 , m_isomRect.y + m_isomRect.h / 2 });
		if (m_powerhouse)
		{
			m_powerhouse->draw(m_mainRenderer, { m_isomRect.x + m_isomRect.w / 2 , m_isomRect.y + m_isomRect.h / 2 });
		}
	}

	if (selected) {
		SDL_RenderCopy(m_mainRenderer, m_shadowTexture, NULL, &m_isomRectLifted);
	}
}

void CTile::quit() {

}