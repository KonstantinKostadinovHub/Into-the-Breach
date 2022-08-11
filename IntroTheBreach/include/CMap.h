#pragma once

#include <string>

using std::string;

class CMap {
public:
	CMap();
	~CMap();

	static const int M_SIZE = 8;

	static const char TILE = '0';
	static const char FLUID = 'W';
	static const char MOUNTAIN = 'M';
	static const char TREE = 'T';
	static const char RANDOM = 'X';
	static const char PHOUSE1 = '1';
	static const char PHOUSE2 = '2';
	static const char PHOUSE3 = '3';
	static const char UNDEFINED = '~';

	static const int PHOUSE_CNT = 3;

	string m_biome;
	char m_map[M_SIZE][M_SIZE];
	
	void init();
	void set(char map[M_SIZE][M_SIZE]);

private:
	void reset();
	void generate();
};