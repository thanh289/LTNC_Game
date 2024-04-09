#include "Col.h"

void Collumn::SetPos(int x, int y)
{
    Xpos = x;
    Ypos = y;
    setSrc(0, 0, 52, 320);
    setDest(Xpos, Ypos, 52, 320);
}

void Collumn::CollumnRender(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Collumn::ColMove()
{
    if(ColState)
    {
        Xpos-=3;
        setDest(Xpos, Ypos , 53, 320);
    }
}

void Collumn::MoveUp()
{
    Ypos -= 0.5;
    setDest(Xpos, Ypos, 53, 320);
}

void Collumn::MoveDown()
{
    Ypos += 0.5;
    setDest(Xpos, Ypos, 53, 320);
}

void Collumn::Stop()
{
    ColState = false;
}

void Collumn::Continue()
{
    ColState = true;
}
