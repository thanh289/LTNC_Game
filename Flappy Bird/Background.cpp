#include "Background.h"


void Background::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
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

void Background::Continue()
{
    GroundState = true;
}


