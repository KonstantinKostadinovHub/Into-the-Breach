#include "Health.h"

SDL_Texture* Health::m_HEALTH_TEXTURE;

Health::Health() {
	m_rect.w = 10;
	m_rect.h = 5;
}

Health::Health(int2 coords, int w) {
	m_rect = {coords.x, coords.y, w, HEALTH_H};
}

Health::~Health() {
}

void Health::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_HEALTH_TEXTURE, NULL, &m_rect);
}
