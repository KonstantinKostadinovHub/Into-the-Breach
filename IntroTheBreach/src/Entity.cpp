#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(int st_tileRow, int st_tileCol)
{
	m_rect.w = 100;
	m_rect.h = 100;
	
	moveToTile(st_tileRow, st_tileCol);
}

Entity::~Entity() {
}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}

void Entity::moveToTile(int tileRow, int tileCol) {
	m_curTile.first = tileRow;
	m_curTile.second = tileCol;

	//Change rect
}
