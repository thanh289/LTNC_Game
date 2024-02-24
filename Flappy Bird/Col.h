#pragma once
#include "Object.h"
#include "Player.h"

class Collumn :public Object
{
private:
    int Xpos;
    int Ypos;
    bool ColState = true;
public:

    void SetPos(int x, int y);

    void CollumnRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest);

    void MoveUp();

    void MoveDown();

    void Stop();

    void Continue();
};
