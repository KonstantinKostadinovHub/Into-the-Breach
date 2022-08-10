#include "CMap.h"
#include <iostream>

CMap::CMap() {
	m_biome = "0";
}

CMap::~CMap() {

}

void CMap::init() {
    if (m_map[0][0] != UNDEFINED) {
        reset();

        return;
    }

    generate();
}

void CMap::set(char map[M_SIZE][M_SIZE]) {
	for (int yy = 0; yy < M_SIZE; yy++) {
		for (int xx = 0; xx < M_SIZE; xx++) {
			m_map[xx][yy] = map[xx][yy];
		}
	}
}

void CMap::reset() {
    for (int yy = 0; yy < M_SIZE; yy++) {
        for (int xx = 0; xx < M_SIZE; xx++) {
            if (m_map[xx][yy] == RANDOM) {
                int terrainType = rand() % 11;

                if (terrainType == 0) {
                    m_map[xx][yy] = FLUID;
                }
                else if (terrainType == 1) {
                    m_map[xx][yy] = MOUNTAIN;
                }
                else if (terrainType == 2) {
                    m_map[xx][yy] = TREE;
                }
                else {
                    m_map[xx][yy] = TILE;
                }
            }
        }
    }
}

void CMap::generate() {
    for (int yy = 0; yy < M_SIZE; yy++) {
        for (int xx = 0; xx < M_SIZE; xx++) {
            int terrainType = rand() % 4;

            switch (terrainType) {
            case 0:
                m_map[xx][yy] = FLUID;
                break;

            case 1:
                m_map[xx][yy] = FLUID;
                break;

            case 2:
                m_map[xx][yy] = MOUNTAIN;
                break;

            case 3:
                m_map[xx][yy] = TREE;
                break;

            default:
                m_map[xx][yy] = TILE;
                break;
            }
        }
    }


    int currX;
    int currY;

    for (int j = 0; j < 2; j++) {
        currX = j * M_SIZE / 2;
        currY = j * M_SIZE / 2;

        m_map[currX][currY] = TILE;

        for (int i = 0; i < M_SIZE * M_SIZE * 2 / 3; i++) {
            int dir = rand() % 4;

            switch (dir) {
            case 0:
                if (currX < M_SIZE - 1) {
                    currX++;
                }
                else {
                    i--;
                }
                break;

            case 1:
                if (currX > 0) {
                    currX--;
                }
                else {
                    i--;
                }
                break;

            case 2:
                if (currY < M_SIZE - 1) {
                    currY++;
                }
                else {
                    i--;
                }
                break;

            case 3:
                if (currY > 0) {
                    currY--;
                }
                else {
                    i--;
                }
                break;

            default:
                break;
            }

            m_map[currX][currY] = TILE;
        }
    }

    for (int xy = 0; xy <= M_SIZE / 2; xy++) {
        m_map[xy][xy] = TILE;
        m_map[xy + 1][xy] = TILE;
    }
}
