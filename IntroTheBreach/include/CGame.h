#pragma once

#include <SDL.h>
#include <iostream>

using std::string;

class CGame {
public:
	CGame();
	~CGame();

	SDL_Renderer* m_mainRenderer;

	string m_bgrTextureFile;
	string m_bgrTextureOverlayFile;

	SDL_Texture* m_bgrTexture;
	SDL_Texture* m_bgrTextureOverlay;
	SDL_Rect m_bgrRect;

	void init(SDL_Renderer* renderer);
	void update();
	void draw();
	void quit();
};