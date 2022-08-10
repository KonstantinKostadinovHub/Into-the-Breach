#include "CTree.h"

string CTree::m_type = "tree";
int CTree::m_maxHealth = 1;

CTree::CTree() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;
	m_rect = { 0, 0, 1, 1 };

	m_health = 1;
}

CTree::~CTree() {

}

string CTree::getType() {
	return m_type;
}

void CTree::init(SDL_Renderer* renderer, SDL_Texture* texture, int2 size) {
	m_mainRenderer = renderer;

	m_texture = texture;
	m_rect.w = size.x;
	m_rect.h = size.y;

	m_health = m_maxHealth;
}

//void CTree::update() {
//
//}

void CTree::draw() {
	SDL_RenderCopy(m_mainRenderer, m_texture, NULL, &m_rect);
}

void CTree::quit() {

}
