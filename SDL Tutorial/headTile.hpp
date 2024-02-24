#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "headTexture.hpp"




class Tile
{
    public:
        Tile( int x, int y, int tileType );

        void render( SDL_Rect& camera, LTexture gTileTexture, SDL_Renderer* mRenderer);

        int getType();

        SDL_Rect getBox();

    private:
        SDL_Rect mBox;

        int mType;
};



