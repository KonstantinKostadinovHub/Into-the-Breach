#include "CNoTerrain.h"

string CNoTerrain::m_type = "none";

CNoTerrain::CNoTerrain() {
	m_mainRenderer = nullptr;

	m_texture = nullptr;
	m_rect = { 0, 0, 1, 1 };

	m_health = -1;
}

CNoTerrain::~CNoTerrain() {

}

string CNoTerrain::getType() {
	return m_type;
}

//void CNoTerrain::update() {
//
//}

void CNoTerrain::draw() {

}


void CNoTerrain::quit() {

}
