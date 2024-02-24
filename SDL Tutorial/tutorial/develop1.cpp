#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;


class LTexture
{
    public:
       LTexture();

       ~LTexture();

       SDL_Texture* loadFromFile(string path);

       void render(int x, int y, SDL_Rect* clip = NULL);

       void setColor(Uint8 red, Uint8 green, Uint8 blue);

       void free();

       int getWidth() {return mWidth;}

       int getHeight() {return mHeight;}

    private:
        SDL_Texture* mTexture; //mainTexture;

        int mWidth;
        int mHeight;
};


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int WALKING_ANIMATION_FRAMES = 4;
string WINDOW_TITLE = "TUTORIAL";
string IMG1 = "";
string IMG2 = "";



void logErrorAndExit(const char* msg, const char* error);
void waitUntilKeyPressed();
void close();
SDL_Window* initWindow();
SDL_Renderer* createRenderer();
void walkingFoo();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;




LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

SDL_Texture* LTexture::loadFromFile(string path)
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL)
        logErrorAndExit("loadImage", IMG_GetError());
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255)); //red: 0, green: 255, blue: 255
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            logErrorAndExit("createTexture", SDL_GetError());
        else
        {
            mWidth = SCREEN_WIDTH;
            mHeight = SCREEN_HEIGHT;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;

    return mTexture;
}


void LTexture::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if(clip != NULL)
    {
        renderQuad.h = clip->h;
        renderQuad.w = clip->w;
    }

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}


void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}



//MAIN
int main(int argc, char* argv[])
{
    gWindow = initWindow();
    gRenderer = createRenderer();

    walkingFoo();

    //waitUntilKeyPressed();
    close();

    return 0;

}




void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                   "%s: %s", msg, error);

    SDL_Quit();
}


void waitUntilKeyPressed()
{
    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
        }
        SDL_Delay(100);
    }
}



void close()
{
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
}


SDL_Window* initWindow()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("initWindow", SDL_GetError());

    SDL_Window* gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(gWindow == NULL)
        logErrorAndExit("createWindow", SDL_GetError());

    return gWindow;
}


SDL_Renderer* createRenderer()
{
    SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(gRenderer == NULL)
        logErrorAndExit("createRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return gRenderer;
}


void walkingFoo()
{
    SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

    LTexture backgroundFoo;
    LTexture gSpriteSheetTexture;


    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 64;
    gSpriteClips[0].h = 205;

    gSpriteClips[1].x = 64;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 64;
    gSpriteClips[1].h = 205;

    gSpriteClips[2].x = 128;
    gSpriteClips[2].y = 0;
    gSpriteClips[2].w = 64;
    gSpriteClips[2].h = 205;

    gSpriteClips[3].x = 192;
    gSpriteClips[3].y = 0;
    gSpriteClips[3].w = 64;
    gSpriteClips[3].h = 205;


    SDL_Event e;
    bool quit = false;
    int frame = 0;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );


        //background
        backgroundFoo.loadFromFile("image/background.png");
        backgroundFoo.render(0, 0);

        //walking foo
        gSpriteSheetTexture.loadFromFile("image/foo.png");
        SDL_Rect* currentClips = &gSpriteClips[frame/4];
        gSpriteSheetTexture.render((SCREEN_WIDTH - currentClips->w)/2, (SCREEN_HEIGHT - currentClips->h)/2,  currentClips);

        SDL_RenderPresent(gRenderer);

        ++frame;
        if(frame/4 >= WALKING_ANIMATION_FRAMES)
        {
            frame = 0;
        }
    }

}
