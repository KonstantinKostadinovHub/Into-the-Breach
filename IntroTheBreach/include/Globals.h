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

void getScreenDetails(int& w, int& h);