#include "Globals.h"

using std::ifstream;

int SCREEN_W;
int SCREEN_H;

char align_with;

int fps = 30;

SDL_DisplayMode SCREEN_RES;

void getScreenDetails(int& w, int& h)
{
    ifstream tmp;
    tmp.open("config\\screen.txt");
    string tmp1, tmp2;
    tmp >> tmp1 >> w >> tmp2 >> h;
    tmp.close();

    SDL_GetCurrentDisplayMode(0, &SCREEN_RES);

    if (SCREEN_H < SCREEN_W * 576 / 1024)
    {
        align_with = 'w';
    }
    else
    {
        align_with = 'h';
    }
}