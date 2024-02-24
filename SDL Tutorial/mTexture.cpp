#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "headTexture.hpp"
#include "headWindow.hpp"
using namespace std;




LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}


SDL_Texture* LTexture::loadFromFile(string path, SDL_Renderer* mRenderer)
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL)
        cout<<"Failed to load image! Error: "<<IMG_GetError();
    else
    {
        //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255)); //red: 0, green: 255, blue: 255
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if(newTexture == NULL)
            cout<<"Failed to create text from surface! Error: "<<SDL_GetError();
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;

    return mTexture;
}


SDL_Texture* LTexture::loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* mRenderer, TTF_Font* mFont)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textureText.c_str(), textColor);
    if(textSurface == NULL)
        cout<<"Failed to render text surface! Error: "<<TTF_GetError();
    else
    {
        mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
        if(mTexture == NULL)
            cout<<"Failed to create texture from rendered text! Error: "<<TTF_GetError();
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return mTexture;
}



void LTexture::render(int x, int y, SDL_Renderer* mRenderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip != NULL)
    {
        renderQuad.h = clip->h;
        renderQuad.w = clip->w;
    }

    SDL_RenderCopy(mRenderer, mTexture, clip, &renderQuad);
}



void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}


int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

