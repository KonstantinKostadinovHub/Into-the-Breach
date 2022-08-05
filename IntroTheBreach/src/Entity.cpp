#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(int st_tileCol, int st_tileRow)
{
	m_rect.w = 100;
	m_rect.h = 100;
	
	moveToTile(st_tileCol, st_tileRow);
}

Entity::~Entity() {
}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}

void Entity::moveToTile(int tileCol, int tileRow) {
	m_curTile.first = tileCol;
	m_curTile.second = tileRow;

	//Change rect
}

void Entity::setIsometricCoords(int2 centerCoords) {
	m_rect.x = centerCoords.x - m_rect.w / 2;
	m_rect.y = centerCoords.y - m_rect.h / 2;
}