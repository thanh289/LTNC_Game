#pragma once
#include <iostream>
#include "Object.h"

class Background :public Object
{
private:
    int XGround;
    bool GroundState = true;
public:

	void NormalRender(SDL_Renderer* ren);

	void AdvanceRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest);

	void SetGround(int x);

    void Move();

    void Stop();

    void Continue();
};


