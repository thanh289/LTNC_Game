#pragma once
#include "Object.h"
#include <SDL.h>

class Button :public Object
{
private:
    const int BUTTON_WIDTH = 80;
    const int BUTTON_HEIGHT = 24;

public:
    void Render(SDL_Renderer* ren);

    bool HandleEvent(SDL_Event *e);
};
