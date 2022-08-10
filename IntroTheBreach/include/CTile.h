#pragma once

#include <string>
#include <SDL.h>

using std::string;

#include "Engine.h"
#include "InputManger.h"
#include "Powerhouse.h"

class CTile {
public:
	CTile();
	~CTile();

	static int m_gridSize;

	int z_add;

	bool hovered;
	bool selected;

	SDL_Renderer* m_mainRenderer;

	SDL_Texture* m_texture;
	SDL_Texture* m_shadow_texture;

	button m_button;
	SDL_Rect m_rectLifted;
	SDL_Rect m_isomRect;
	SDL_Rect m_isomRectLifted;

	Powerhouse* m_powerhouse;

	void init(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* shadow_texture, int2 coord, int size);
	void update();
	void draw();
	void quit();

	void addPowerhouse(SDL_Renderer* renderer, POWERHOUSE type, int team);
};