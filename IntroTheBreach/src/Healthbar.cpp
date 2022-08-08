#include "Healthbar.h"

SDL_Texture* Healthbar::m_HEALTHBAR_TEXTURE;

#include <iostream>

Healthbar::Healthbar() {
}

Healthbar::Healthbar(int health, int2 centerCoords) {
	m_rect = {centerCoords.x - HEALTHBAR_W / 2, centerCoords.y - HEALTHBAR_H / 2 , HEALTHBAR_W, HEALTHBAR_H};
	m_healthDepleted = false;

	m_maxHealth = health;

	float health_w = (m_rect.w - (HEALTHBAR_FRAME_W * 2) - (health - 1.f)) / health;
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

	for (int i = 0; i < m_health.size(); i++) {
		m_health[i].draw(renderer);
	}
}

void Healthbar::decreaseHealth(int decrease) {
	if (decrease >= m_health.size()) {
		m_health.clear();
		m_healthDepleted = true;
		return;
	}
	else {
		for (int i = 0; i < decrease; i++) {
			m_health.erase(m_health.begin() + m_health.size() - i - 1);
		}
	}
}

void Healthbar::setCoords(int2 coords) {
	int2 coordChange = int2(coords.x - m_rect.x - HEALTHBAR_W / 2, coords.y - m_rect.y - HEALTHBAR_H / 2);
	m_rect.x = coords.x - HEALTHBAR_W / 2;
	m_rect.y = coords.y - HEALTHBAR_H / 2;
	for (int i = 0; i < m_health.size(); i++) {
		m_health[i].moveCoords(coordChange);
	}
}
