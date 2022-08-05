#pragma once

#include <iostream>
#include <fstream>

#include <SDL.h>

using std::string;

extern int fps;
const int tps = 50;

extern SDL_DisplayMode SCREEN_RES;

extern int SCREEN_W;
extern int SCREEN_H;

extern char align_with;

const float GRAVITY_PULL = 0.5;

const int PROJECTILE_SIZE = 20;

const int HEALTHBAR_W = 36;
const int HEALTHBAR_H = 16;
const int HEALTHBAR_FRAME_W = 2;
const int HEALTHBAR_OFFSET_FROM_ENTITY = 20;
const int HEALTH_H = 12;

void getScreenDetails(int& w, int& h);