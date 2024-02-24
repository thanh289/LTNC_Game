#include "Background.h"


void Background::NormalRender(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), NULL, NULL);

}

void Background::AdvanceRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest)
{

    SDL_RenderCopy(ren, getTexture(), &src, &dest);
}


void Background::SetGround(int x)
{
    XGround = x;
    setSrc(0, 0, 336, 112);
    setDest(XGround, 640 - 112, 336, 112);

}

void Background::Move()
{
    if(GroundState)
    {
        XGround-=3;
        setDest(XGround, 640-112 , 336, 112);
    }
}

void Background::Stop()
{
    GroundState = false;
}

