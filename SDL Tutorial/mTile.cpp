#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "headTexture.hpp"
#include "headTile.hpp"




Tile::Tile(int x, int y, int tileType)
{
    mBox.x = x;
    mBox.y = y;

    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    mType = tileType;
}


void Tile::render(SDL_Rect& camera, LTexture gTileTexture, SDL_Renderer* mRenderer)
{
    if(checkCollision(camera, mBox))
        gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, mRenderer, &gTileClips[mType]);
}


int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
