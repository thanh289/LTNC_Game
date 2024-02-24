#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "headTexture.hpp"
#include "headWindow.hpp"
using namespace std;




LWindow::LWindow()
{
    mWindow = NULL;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimized = false;
    mWidth = 0;
    mHeight = 0;
}

SDL_Window* LWindow::init(int screenW, int screenH, const char* Title)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        cout<<"Failed to init window! Error: "<<SDL_GetError();

    mWindow = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(mWindow == NULL)
        cout<<"Failed to create window! Error: "<<SDL_GetError();


    if(mWindow != NULL)
    {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = screenW;
        mHeight = screenH;
    }

    return mWindow;
}

SDL_Renderer* LWindow::createRenderer()
{
    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void LWindow::handleEvent(SDL_Event& e)
{
    if(e.type == SDL_WINDOWEVENT)
    {
        bool updateCation = false;

        switch(e.window.event)
        {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                SDL_RenderPresent(mRenderer);
                break;

            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(mRenderer);
                break;

            case SDL_WINDOWEVENT_ENTER:
                mMouseFocus = true;
                updateCation = true;
                break;

            case SDL_WINDOWEVENT_LEAVE:
                mMouseFocus = false;
                updateCation = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mKeyboardFocus = true;
                updateCation = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                mKeyboardFocus = false;
                updateCation = true;
                break;

            case SDL_WINDOWEVENT_MINIMIZED:
                mMinimized = true;
                break;

            case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimized = false;
                break;

            case SDL_WINDOWEVENT_RESTORED:
                mMinimized = false;
                break;
        }

        if(updateCation)
        {
            stringstream caption;
            caption << "SDL Tutorial - MouseFocus: " << ( ( mMouseFocus ) ? "On" : "Off" ) << " KeyboardFocus: " << ( ( mKeyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle(mWindow, caption.str().c_str());
        }

    }

    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
    {
        if(mFullScreen)
        {
            SDL_SetWindowFullscreen(mWindow, 0);
            mFullScreen = false;
        }

        else
        {
            SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
            mFullScreen = true;
            mMinimized = false;
        }
    }

}


void LWindow::free()
{

    SDL_DestroyWindow( mWindow );
    SDL_DestroyRenderer(mRenderer);

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}


int LWindow::getWidth()
{
    return mWidth;
}

int LWindow::getHeight()
{
    return mHeight;
}

SDL_Renderer* LWindow::getRenderer()
{
    return mRenderer;
}

bool LWindow::hasMouseFocus()
{
    return mMouseFocus;
}

bool LWindow::hasKeyboardFocus()
{
    return mKeyboardFocus;
}

bool LWindow::isMinimized()
{
    return mMinimized;
}
