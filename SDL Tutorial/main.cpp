#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "headTexture.hpp"
#include "headWindow.hpp"
#include "headTime.hpp"
#include "headWindow.hpp"

#include "headTile.hpp"
using namespace std;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* GAME_TITLE = "GAME v1.0";

LWindow gWindow;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
LTimer timer;
LTexture gBGTexture; //bg
LTexture gTimeTextTexture; //time
LTexture gDotTexture; //motion

void ttfInit();


//DOT
class Dot
{
    public:
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        static const int DOT_VEL = 10;

        Dot(int x, int y);

        void handleEvent(SDL_Event& e);

        void Move();

        void setCamera(SDL_Rect& camera);

        void render(LTexture gDotTexture);

        int getPosX();
        int getPosY();

    private:
        int mPosX, mPosY;

        int mVelX, mVelY;


};


Dot::Dot(int x, int y)
{
    mPosX = x;
    mPosY = y;

    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }

    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::Move()
{
    mPosX += mVelX;
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY;
    }
}




void Dot::render(LTexture gDotTexture)
{
    gDotTexture.render(mPosX, mPosY, gRenderer);
}














int main(int argc, char* argv[])
{
    //INIT
    gWindow.init(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    gRenderer = gWindow.createRenderer();
    ttfInit();

    gBGTexture.loadFromFile("image/background.png", gRenderer);
    stringstream timeText;
    SDL_Color textColor = {255, 255, 0, 225};

    gDotTexture.loadFromFile("image/dot.bmp", gRenderer);
    Dot dot(Dot::DOT_WIDTH/2, Dot::DOT_HEIGHT/2);

    //


    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;

            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_s)
                {
                    //start/ stop
                    if(timer.isStarted())
                        timer.stop();
                    else
                        timer.start();
                }

                //pause/ unpause
                else if(e.key.keysym.sym == SDLK_p)
                {
                    if(timer.isPaused())
                        timer.unpause();
                    else
                        timer.pause();
                }
            }

            gWindow.handleEvent(e);
            dot.handleEvent(e);
        }

        if(!gWindow.isMinimized())
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            //
            gBGTexture.render(0, 0, gRenderer);


            timeText.str("");
            timeText<<"Time: "<<(timer.getTicks() / 1000.f);
            gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gRenderer, gFont);
            gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth(), 0, gRenderer);


            dot.Move();
            dot.render(gDotTexture);

            SDL_RenderPresent(gRenderer);

            //
        }

    }

    gWindow.free();
    return 0;
}
















void ttfInit()
{
    if(TTF_Init() ==-1)
        cout<<"Failed to init ttf! Error: "<<TTF_GetError();

    gFont = TTF_OpenFont("font/lazy.ttf", 28);
    if(gFont == NULL)
        cout<<"Failed to load font! Error: "<<TTF_GetError();

}



