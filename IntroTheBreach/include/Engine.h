#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using std::string;

#define D(x) std::cerr << "|| at: " << __LINE__ << " " << #x << " = " << (x) << ";";

struct int2 {
	int2();
	int2(int a, int b);
	~int2();

	int x;
	int y;
};

struct int3 {
	int3();
	int3(int a, int b, int c);
	~int3();

	int x;
	int y;
	int z;
};

struct float2 {
	float2();
	float2(float a, float b);
	~float2();

	float x;
	float y;
};

struct float3 {
	float3();
	float3(float a, float b, float c);
	~float3();

	float x;
	float y;
	float z;
};

struct double2 {
	double2();
	double2(double a, double b);
	~double2();

	double x;
	double y;
};

struct double3 {
	double3();
	double3(double a, double b, double c);
	~double3();

	double x;
	double y;
	double z;
};

struct SDL_Texture2 {
	SDL_Texture2();
	SDL_Texture2(SDL_Texture* img, SDL_Texture* overlay_img);
	~SDL_Texture2();

	SDL_Texture* texture;
	SDL_Texture* overlay;
};

extern int TILE_SIZE;
extern int ISOM_TILE_W;
extern int ISOM_TILE_H;
extern int GRID_SIZE;

SDL_Texture* loadTexture(SDL_Renderer* renderer, string filename);
SDL_Texture* loadText(SDL_Renderer* renderer, string filename, SDL_Color text_color, string text);

void giveTileSize(int tileSize, int isomTileW, int isomTileH, int gridSize);
int2 normalToIsom(int2 coords);
int2 gridToScreenCoords(int2 gridCoords);
float2 floatGridToScreenCoords(float2 gridCoord);
int2 screenToGridCoords(int2 screenCoords);

bool colliding(SDL_Rect rect1, SDL_Rect rect2);
bool collidingRectAndPoint(SDL_Rect rect, int2 point);

int getNumSize(int num);
string intToStr(int num);

string wstrToStr(const std::wstring& wstr);