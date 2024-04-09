#include "Object.h"
#include <SDL_image.h>

void Object::setSrc(int x, int y, int w, int h)
{
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}

void Object::setDest(int x, int y, int w, int h)
{
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}


void Object::CreateTexture(const char* address, SDL_Renderer* ren)
{
    SDL_Surface* surface;
	surface = IMG_Load(address);
	Tex = SDL_CreateTextureFromSurface(ren, surface);
}



SDL_Texture* Object::getTexture()
{
    return Tex;
}

SDL_Rect& Object::getSrc()
{
    return src;
}

SDL_Rect& Object::getDest()
{
    return dest;
}
