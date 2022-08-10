#include "Health.h"

SDL_Texture* Health::m_HEALTH_TEXTURE;
SDL_Texture* Health::m_ENEMY_HEALTH_TEXTURE;

Health::Health() {
}

Health::Health(int2 coords, int w, bool enemy) {
	m_rect = {coords.x, coords.y, w, HEALTH_H};
	m_enemy = enemy;
}

Health::~Health() {
}

void Health::draw(SDL_Renderer* renderer) {
	if (m_enemy) {
		SDL_RenderCopy(renderer, m_ENEMY_HEALTH_TEXTURE, NULL, &m_rect);
	}
	else {
		SDL_RenderCopy(renderer, m_HEALTH_TEXTURE, NULL, &m_rect);
	}
}

void Health::moveCoords(int2 coordsChange) {
	m_rect.x += coordsChange.x;
	m_rect.y += coordsChange.y;
}
