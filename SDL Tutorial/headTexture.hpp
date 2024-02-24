#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "headWindow.hpp"

using namespace std;

class LTexture
{
public:
    LTexture();

    SDL_Texture* loadFromFile(string path, SDL_Renderer* mRenderer);

    SDL_Texture* loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* mRenderer, TTF_Font* mFont);

    void render(int x, int y, SDL_Renderer* mRenderer, SDL_Rect* clip = NULL);

    void free();

    int getWidth();

    int getHeight();


private:
    SDL_Texture* mTexture; //mainTexture;

    int mWidth;
    int mHeight;
};

