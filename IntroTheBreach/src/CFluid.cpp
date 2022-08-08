#include "CFluid.h"

string CFluid::m_type = "fluid";
int CFluid::m_maxHealth = -1;

CFluid::CFluid() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;
	m_rect = { 0, 0, 1, 1 };

	m_health = 1;
}

CFluid::~CFluid() {

}

string CFluid::getType() {
	return m_type;
}

void CFluid::init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size) {
	m_mainRenderer = renderer;

	m_texture = texture;
	m_rect.w = size.x;
	m_rect.h = size.y;

	m_health = m_maxHealth;
}

//void CFluid::update() {
//
//}

void CFluid::draw() {
	SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_rect);
}

void CFluid::quit() {

}
