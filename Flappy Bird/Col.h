#pragma once
#include "Object.h"
#include "Player.h"

class Collumn :public Object
{
private:
    double Xpos;
    double Ypos;
    bool ColState = true;
public:

    void SetPos(int x, int y);

    void CollumnRender(SDL_Renderer* ren);

    void ColMove();

    void MoveUp();

    void MoveDown();

    void Stop();

    void Continue();
};
