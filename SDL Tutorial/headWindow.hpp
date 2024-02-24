#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class LWindow
{
    public:
        LWindow();

        SDL_Window* init(int screenW, int screenH, const char* Title);

        SDL_Renderer* createRenderer();

        void handleEvent(SDL_Event& e);

        void free();

        int getWidth();
        int getHeight();
        SDL_Renderer* getRenderer();

        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();

    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        int mWidth;
        int mHeight;

        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;

};





