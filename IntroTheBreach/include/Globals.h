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

const int HEALTHBAR_W = 36;
const int HEALTHBAR_H = 16;
const int HEALTHBAT_FRAME_W = 2;
const int HEALTH_H = 12;

void getScreenDetails(int& w, int& h);