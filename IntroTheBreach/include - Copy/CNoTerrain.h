#pragma once

#include "CTerrain.h"

class CNoTerrain : public CTerrain {
public:
	CNoTerrain();
	~CNoTerrain();

	static string m_type;

	string getType();

	//void update();
	void draw();
	void quit();
};