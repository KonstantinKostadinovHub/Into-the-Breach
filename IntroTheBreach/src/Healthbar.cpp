#include "Healthbar.h"

SDL_Texture* Healthbar::m_HEALTHBAR_TEXTURE;

#include <iostream>

Healthbar::Healthbar() {
}

Healthbar::Healthbar(int health, int2 coords) {
	m_rect = { coords.x, coords.y , HEALTHBAR_W, HEALTHBAR_H };

	m_maxHealth = health;
	m_healthLeft = health;

	float health_w = (m_rect.w - (HEALTHBAT_FRAME_W * 2) - (health - 1.f)) / health;
	int2 health_coords(m_rect.x + 2, m_rect.y + 2);
	float leftPixels = 0;
	bool thicker = false;

	for (int i = 0; i < health; i++) {
		m_health.push_back(Health(health_coords, health_w + thicker));
		if (thicker) {
			health_coords.x++;
			thicker = false;
		}


		leftPixels += health_w - int(health_w);
		health_coords.x += health_w + 1;

		if (leftPixels >= 1) {
			leftPixels--;
			thicker = true;
		}
	}
}

Healthbar::~Healthbar() {
}

void Healthbar::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, m_HEALTHBAR_TEXTURE, NULL, &m_rect);

	for (int i = 0; i < m_healthLeft; i++) {
		m_health[i].draw(renderer);
	}
}
