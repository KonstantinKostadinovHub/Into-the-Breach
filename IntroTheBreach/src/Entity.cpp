#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(int st_tileCol, int st_tileRow, int health) {
	m_rect.w = 60;
	m_rect.h = 78;
	
	moveToTile(st_tileCol, st_tileRow);

	m_healthLeft = health;
	m_healthbar = Healthbar(health, int2(m_rect.x + m_rect.w / 2, m_rect.y - HEALTHBAR_OFFSET_FROM_ENTITY));
}

Entity::~Entity() {
}

void Entity::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
	m_healthbar.draw(renderer);
}

void Entity::moveToTile(int tileCol, int tileRow) {
	m_curTile.first = tileCol;
	m_curTile.second = tileRow;

	//Change rect
	int2 temp = gridToScreenCoords(int2(tileCol * TILE_SIZE, tileRow * TILE_SIZE));
	temp.x += ISOM_TILE_W / 2;

	setCenterCoords(temp);
}

void Entity::setCenterCoords(int2 centerCoords) {
	m_rect.x = centerCoords.x - m_rect.w / 2;
	m_rect.y = centerCoords.y - m_rect.h / 2;
}