#pragma once

#include <iostream>
#include <fstream>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using std::string;

#define D(x) std::cerr << "|| at: " << __LINE__ << " " << #x << " = " << (x) << ";";

SDL_Texture* loadTexture(SDL_Renderer* renderer, string filename);
SDL_Texture* loadText(SDL_Renderer* renderer, string filename, SDL_Color text_color, string text);

bool colliding(SDL_Rect rect1, SDL_Rect rect2);

void getScreenDetails(int& w, int& h);

extern int fps;
const int tps = 50;

extern SDL_DisplayMode SCREEN_RES;

extern int SCREEN_W;
extern int SCREEN_H;

extern char align_with;

struct int2 {
	int2();
	int2(int a, int b);
	~int2();

	int x;
	int y;
};

struct float2 {
	float2();
	float2(int a, int b);
	~float2();

	float x;
	float y;
};

struct double2 {
	double2();
	double2(int a, int b);
	~double2();

	double x;
	double y;
};