#include "CMountain.h"

string CMountain::m_type = "mountain";
int CMountain::m_maxHealth = 3;

CMountain::CMountain() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;
	m_rect = { 0, 0, 1, 1 };

	m_health = 1;
}

CMountain::~CMountain() {

}

string CMountain::getType() {
	return m_type;
}

void CMountain::init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size) {
	m_mainRenderer = renderer;

	m_texture = texture;
	m_rect.w = size.x;
	m_rect.h = size.y;

	m_health = m_maxHealth;
}

//void CMountain::update() {
//
//}

void CMountain::draw() {
	SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_rect);
}


void CMountain::quit() {

}
