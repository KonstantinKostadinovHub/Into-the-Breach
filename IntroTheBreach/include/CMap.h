#pragma once

#include <string>

using std::string;

class CMap {
public:
	CMap();
	~CMap();

	static const int M_SIZE = 8;

	string m_biome;
	char m_map[M_SIZE][M_SIZE];

	void set(char map[M_SIZE][M_SIZE]);
};