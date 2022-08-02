#include "Engine.h"

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

bool colliding(SDL_Rect rect1, SDL_Rect rect2) {
    if (rect1.x < rect2.x + rect2.w &&
        rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h &&
        rect1.y + rect1.h > rect2.y) {
        return true;
    }
    return false;
}
