#pragma once
#include "Object.h"
#include "Col.h"

class Player :public Object
{
    private:
        double Ypos = 320;
        double accelerator1 = 0;
        double accelerator2 = 0;
        double jumpHeight = -4;
        double angle = 0;
        bool inJump = false;
        bool Pause = false;
        SDL_Texture* Tex1;
        SDL_Texture* Tex2;
        int animationTimer = 0;


    public:
        void Gravity();
        void Jump();
        void Die();
        void Revive();
        void Stop();
        void Continue();
        bool GetCollision(SDL_Rect Col, int ob_W, int ob_H);
        void AliveRender(SDL_Renderer* ren);
        void DieRender(SDL_Renderer* ren);
        void CreateTexture1(const char* address, SDL_Renderer* ren);
        void CreateTexture2(const char* address, SDL_Renderer* ren);
};
