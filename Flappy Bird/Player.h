#pragma once
#include "Object.h"
#include "Col.h"

class Player :public Object
{
    private:
        double gravity = 0.1;
        double Ypos = 320;
        double accelerator = 0;
        double jumpHeight = -4;
        bool inJump = false;
        SDL_Texture* Tex1;
        SDL_Texture* Tex2;
        int animationTimer = 0;
        Uint32 curJumpTime = 0;


    public:
        void Gravity();
        void Jump();
        void Die();
        void Revive();
        bool JumpState();
        bool GetCollision(SDL_Rect Col, int ob_W, int ob_H);
        void AliveRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest);
        void DieRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest);
        void CreateTexture1(const char* address, SDL_Renderer* ren);
        void CreateTexture2(const char* address, SDL_Renderer* ren);
};
