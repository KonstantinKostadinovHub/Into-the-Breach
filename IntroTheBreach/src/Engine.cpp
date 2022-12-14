#include <array>

#include "Engine.h"
#include "Globals.h"

int2::int2() {
    x = 0;
    y = 0;
}

int2::int2(int a, int b) {
    x = a;
    y = b;
}

int2::~int2() {

}

int3::int3() {
    x = 0;
    y = 0;
    z = 0;
}

int3::int3(int a, int b, int c) {
    x = a;
    y = b;
    z = c;
}

int3::~int3() {

}


float2::float2() {
    x = 0;
    y = 0;
}

float2::float2(float a, float b) {
    x = a;
    y = b;
}

float2::~float2() {

}

float3::float3() {
    x = 0;
    y = 0;
    z = 0;
}

float3::float3(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

float3::~float3() {

}


double2::double2() {
    x = 0;
    y = 0;
}

double2::double2(double a, double b) {
    x = a;
    y = b;
}

double2::~double2() {

}

double3::double3() {
    x = 0;
    y = 0;
    z = 0;
}

double3::double3(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

double3::~double3() {

}

int TILE_SIZE;
int ISOM_TILE_W;
int ISOM_TILE_H;
int GRID_SIZE;

SDL_Texture* loadTexture(SDL_Renderer* renderer, string filename) {
    filename = "img\\" + filename;

    SDL_Texture* img;

    SDL_Surface* tmp = SDL_LoadBMP(filename.c_str());
    img = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    return img;
}

SDL_Texture* loadText(SDL_Renderer* renderer, string filename, SDL_Color text_color, string text) {
    SDL_Texture* text_img = nullptr;
    TTF_Font* font = TTF_OpenFont(filename.c_str(), 20);

    SDL_Surface* tmp = TTF_RenderText_Solid(font, text.c_str(), text_color);
    text_img = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    return text_img;
}

void giveTileSize(int tileSize, int isomTileW, int isomTileH, int gridSize) {
    TILE_SIZE = tileSize;
    ISOM_TILE_W = isomTileW;
    ISOM_TILE_H = isomTileH;
    GRID_SIZE = gridSize;
}

int2 normalToIsom(int2 coord) {
    int2 isomCoord;

    isomCoord.x = SCREEN_W / 2 +                           ((coord.x - coord.y) * (ISOM_TILE_W / 2) / TILE_SIZE);
    isomCoord.y = (SCREEN_H - (8 * ISOM_TILE_H / 2)) / 2 + ((coord.x + coord.y) * (ISOM_TILE_H / 4) / TILE_SIZE);

    return isomCoord;
}

int2 gridToScreenCoords(int2 gridCoord) {
    //Centers automaticly
    int2 screenCoord;

    screenCoord.x = gridCoord.x - gridCoord.y + SCREEN_W / 2;// -ISOM_TILE_W / 2;
    screenCoord.y = (gridCoord.x + gridCoord.y) / 2 + (SCREEN_H - ISOM_TILE_H / 2 * (GRID_SIZE + 1)) / 2 + TILE_SIZE / 2;

    return screenCoord;
}

float2 floatGridToScreenCoords(float2 gridCoord) {
    float2 screenCoord;

    screenCoord.x = gridCoord.x - gridCoord.y + SCREEN_W / 2;// -ISOM_TILE_W / 2;
    screenCoord.y = (gridCoord.x + gridCoord.y) / 2 + (SCREEN_H - ISOM_TILE_H / 2 * (GRID_SIZE + 1)) / 2;

    return screenCoord;
}

int2 screenToGridCoords(int2 screenCoords) {
    int2 gridCoord;
    int2 tmp;

    tmp.x = screenCoords.x - SCREEN_W / 2;// +ISOM_TILE_W / 2;
    tmp.y = screenCoords.y - (SCREEN_H - ISOM_TILE_H / 2 * (GRID_SIZE + 1)) / 2 - TILE_SIZE / 2;

    gridCoord.x = tmp.x / 2 + tmp.y;
    gridCoord.y = tmp.y * 2 - gridCoord.x;

    return gridCoord;
}

bool colliding(SDL_Rect rect1, SDL_Rect rect2) {
    if (rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y) {
        return true;
    }
    return false;
}

bool collidingRectAndPoint(SDL_Rect rect, int2 point) {
    if (point.x < rect.x)
    {
        return false;
    }
    if (point.x + 1 > rect.x + rect.w)
    {
        return false;
    }
    if (point.y < rect.y)
    {
        return false;
    }
    if (point.y + 1 > rect.y + rect.h)
    {
        return false;
    }

    return true;
}

SDL_Texture2::SDL_Texture2() {
    texture = nullptr;
    overlay = nullptr;
}

SDL_Texture2::SDL_Texture2(SDL_Texture* img, SDL_Texture* overlay_img) {
    texture = img;
    overlay = overlay_img;
}

SDL_Texture2::~SDL_Texture2() {

}

int getNumSize(int num)
{
    num = abs(num);

    for (int i = 0; i > -1; i++) {
        num /= 10;

        if (num == 0) {
            return i + 1;
        }
    }
}

string intToStr(int num) {
    string ans = "";

    int numSz = getNumSize(num);
    char curr;

    for (int i = 0; i < numSz; i++) {
        curr = num % 10;
        curr += '0';
        ans = curr + ans;

        num /= 10;
    }

    return ans;
}

string wstrToStr(const std::wstring& wstr)
{
    const int BUFF_SIZE = 7;

    if (MB_CUR_MAX >= BUFF_SIZE) {
        throw std::invalid_argument("BUFF_SIZE too small");
    }
    string result;

    #pragma warning(suppress : 4996)
    bool shifts = std::wctomb(nullptr, 0);  // reset the conversion state

    for (const wchar_t wc : wstr)
    {
        std::array<char, BUFF_SIZE> buffer;

        #pragma warning(suppress : 4996)
        const int ret = std::wctomb(buffer.data(), wc);

        if (ret < 0) {
            throw std::invalid_argument("inconvertible wide characters in the current locale");
        }
        buffer[ret] = '\0';  // make 'buffer' contain a C-style string

        result += std::string(buffer.data());
    }
    return result;
}