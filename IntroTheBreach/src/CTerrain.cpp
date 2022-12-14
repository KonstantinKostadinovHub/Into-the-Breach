#include "CTerrain.h"

CTerrain::CTerrain() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;
	m_rect = { 0, 0, 1, 1 };

	m_health = 1;
}

CTerrain::~CTerrain() {

}

string CTerrain::getType() {
	return "ERR";
}

void CTerrain::init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size) {
	m_mainRenderer = renderer;

	m_texture = texture;
	m_rect.w = size.x;
	m_rect.h = size.y;
}

void CTerrain::giveCentralPoint(int2 coord) {
	m_rect.x = coord.x - m_rect.w / 2;
	m_rect.y = coord.y - m_rect.h;
}

void CTerrain::update() {
	//std::cout << "WHY\n";
}

void CTerrain::draw() {
	SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_rect);
}

void CTerrain::quit() {

}
