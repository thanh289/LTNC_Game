#include "Col.h"

void Collumn::SetPos(int x, int y)
{
    Xpos = x;
    Ypos = y;
    setSrc(0, 0, 52, 320);
    setDest(Xpos, Ypos, 52, 320);
}

void Collumn::CollumnRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren, getTexture(), &src, &dest);
}

void Collumn::MoveUp()
{
    if(ColState)
    {
        Xpos-=3;
        setDest(Xpos, Ypos , 53, 320);
    }
}


void Collumn::MoveDown()
{
    if(ColState)
    {
        Xpos-=3;
        setDest(Xpos, Ypos , 53, 320);
    }
}

void Collumn::Stop()
{
    ColState = false;
}

void Collumn::Continue()
{
    ColState = true;
}
