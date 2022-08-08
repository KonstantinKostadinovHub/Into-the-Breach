#include "CMap.h"

CMap::CMap() {
	m_biome = "0";
}

CMap::~CMap() {

}

void CMap::set(char map[M_SIZE][M_SIZE]) {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			m_map[xx][yy] = map[xx][yy];
		}
	}
}
