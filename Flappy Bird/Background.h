#pragma once
#include <iostream>
#include "Object.h"

class Background :public Object
{
private:
    int XGround;
    bool GroundState = true;
public:

	void Render(SDL_Renderer* ren);

	void SetGround(int x);

    void Move();

    void Stop();

    void Continue();
};


