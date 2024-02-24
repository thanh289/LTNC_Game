#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 1200;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;


const char* WINDOW_TITLE = "TUTORIAL";
string IMG1 = "";
string IMG2 = "";
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

void logErrorAndExit(const char* msg, const char* error);
void keyPresses();
void mouseEvent();
void printTime();
void motion();

void close();
void walkingFoo();




//CLASS FOR TEXTURE
class LTexture
{
public:
    LTexture();

    ~LTexture();

    SDL_Texture* loadFromFile(string path);

    SDL_Texture* loadFromRenderedText(string textureText, SDL_Color textColor);

    void render(int x, int y, SDL_Rect* clip = NULL);

    void free();

    int getWidth()
    {
        return mWidth;
    }

    int getHeight()
    {
        return mHeight;
    }

private:
    SDL_Texture* mTexture; //mainTexture;

    int mWidth;
    int mHeight;
};

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
            logErrorAndExit("createTextureFromImage", SDL_GetError());
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;

    return mTexture;
}


SDL_Texture* LTexture::loadFromRenderedText(string textureText, SDL_Color textColor)
{

    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if(textSurface == NULL)
        logErrorAndExit("renderTextSurface", TTF_GetError());
    else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if(mTexture == NULL)
            logErrorAndExit("createTextureFromRenderedText", TTF_GetError());
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

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


//CLASS FOR BUTTON
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4     //Number of act
};

LTexture gButtonSpriteSheetTexture;
//Rec for clip
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];


class LButton
{
public:
    LButton();

    void setPosition(int x, int y);

    void handleEvent(SDL_Event* e);

    void render();

private:
    SDL_Point mPosition;

    LButtonSprite mCurrentSprite;

};


LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if( x < mPosition.x )
            inside = false;

        else if( x > mPosition.x + BUTTON_WIDTH )
            inside = false;

        else if( y < mPosition.y )
            inside = false;


        else if( y > mPosition.y + BUTTON_HEIGHT )
            inside = false;


        if(!inside)
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        else
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;

            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            }
        }
    }
}

void LButton::render()
{
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}



//CLASS FOR TIMER
class LTimer
{
public:
    LTimer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isStarted()
    {
        return mStarted;
    }
    bool isPaused()
    {
        return mPaused && mStarted;
    }

private:
    Uint32 mStartTicks;

    Uint32 mPausedTicks;

    bool mPaused;
    bool mStarted;


};


LTimer::LTimer()
{
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    mStarted = true;

    mPaused = false;

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}


void LTimer::stop()
{
    mStarted = false;

    mPaused = false;

    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    if( mStarted && !mPaused )
    {
        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }

}

void LTimer::unpause()
{
    if( mStarted && mPaused )
    {
        mPaused = false;

        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}


Uint32 LTimer::getTicks()
{
    Uint32 time = 0;

    if(mStarted)
    {
        if(mPaused)
            time = mPausedTicks;
        else
            time = SDL_GetTicks() - mStartTicks;
    }

    return time;
}





//CLASS FOR MOTION
LTexture gDotTexture;
struct Circle
{
   int x, y;
   int r;
};

bool checkCollision(Circle& a, Circle& b);
bool checkCollision(Circle& a, SDL_Rect& b);
double distanceSquared(int x1, int y1, int x2, int y2);


class Dot
{
    public:
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        static const int DOT_VEL = 10;

        Dot(int x, int y);

        void handleEvent(SDL_Event& e);

        void Move(SDL_Rect& square, Circle& circle);

        void render(int camX, int camY);

        Circle& getCollider();

        int getPosX(){return mPosX;}
        int getPosY(){return mPosY;}

    private:
        int mPosX, mPosY;

        int mVelX, mVelY;

        Circle mCollider;

        void shiftColliders();
};



Dot::Dot(int x, int y)
{
    mPosX = x;
    mPosY = y;

    mCollider.r = DOT_WIDTH / 2;

    mVelX = 0;
    mVelY = 0;

    shiftColliders();

}

void Dot::handleEvent(SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_w: mVelY -= DOT_VEL; break;
            case SDLK_s: mVelY += DOT_VEL; break;
            case SDLK_a: mVelX -= DOT_VEL; break;
            case SDLK_d: mVelX += DOT_VEL; break;
        }
    }

    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_w: mVelY += DOT_VEL; break;
            case SDLK_s: mVelY -= DOT_VEL; break;
            case SDLK_a: mVelX += DOT_VEL; break;
            case SDLK_d: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::Move(SDL_Rect& square, Circle& circle)
{

    mPosX += mVelX;
    shiftColliders();

    if((mPosX - mCollider.r < 0 ) || (mPosX + mCollider.r > LEVEL_WIDTH) || checkCollision(mCollider, square) || checkCollision(mCollider, circle))
    {
        mPosX -= mVelX;
        shiftColliders();
    }

    mPosY += mVelY;
    shiftColliders();
    if( ( mPosY - mCollider.r < 0 ) || ( mPosY + mCollider.r > LEVEL_HEIGHT ) || checkCollision( mCollider, square ) || checkCollision( mCollider, circle ))
    {
        mPosY -= mVelY;
        shiftColliders();
    }
}



void Dot::render(int camX, int camY)
{
    //Take its center as the beginning point
    gDotTexture.render(mPosX-mCollider.r-camX, mPosY-mCollider.r-camY);
}


Circle& Dot::getCollider()
{
    return mCollider;
}


void Dot::shiftColliders()
{
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


bool checkCollision( Circle& a, Circle& b )
{
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) )
        return true;

    return false;
}

bool checkCollision(Circle& a, SDL_Rect& b)
{
    //view image in tutorial for understanding easier
    int cX, cY;

    if( a.x < b.x )
        cX = b.x;
    else if( a.x > b.x + b.w )
        cX = b.x + b.w;
    else
        cX = a.x;


    if( a.y < b.y )
        cY = b.y;
    else if( a.y > b.y + b.h )
        cY = b.y + b.h;
    else
        cY = a.y;

    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
        return true;


    return false;
}


double distanceSquared( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}



//CLASS FOR WINDOW
class LWindow
{
    public:
        LWindow();

        SDL_Window* init();

        SDL_Renderer* createRenderer();

        void handleEvent(SDL_Event& e);

        void free();

        int getWidth(){return mWidth;}
        int getHeight(){return mHeight;}

        bool hasMouseFocus(){return mMouseFocus;}
        bool hasKeyboardFocus(){return mKeyboardFocus;}
        bool isMinimized(){return mMinimized;}

    private:
        SDL_Window* mWindow;

        int mWidth;
        int mHeight;

        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;

};

LWindow gWindow;
LTexture gSceneTexture;

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

SDL_Window* LWindow::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("initWindow", SDL_GetError());

    mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(mWindow == NULL)
        logErrorAndExit("createWindow", SDL_GetError());


    if(mWindow != NULL)
    {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
    }

    return mWindow;
}

SDL_Renderer* LWindow::createRenderer()
{
    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL)
        logErrorAndExit("createRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
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
                SDL_RenderPresent(gRenderer);
                break;

            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(gRenderer);
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
	if( mWindow != NULL )
		SDL_DestroyWindow( mWindow );

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}


//MAIN
int main(int argc, char* argv[])
{
    gWindow.init();
    gRenderer = gWindow.createRenderer();


    //walkingFoo();
    //createFont();
    //keyPresses();
    //mouseEvent();
    //printTime();
    //motion();

    gSceneTexture.loadFromFile("image/window.png");

    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;

            gWindow.handleEvent(e);
        }

        if(!gWindow.isMinimized())
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );



            gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth())/2, ( gWindow.getHeight() - gSceneTexture.getHeight())/2);

            SDL_RenderPresent(gRenderer);
        }

    }



    close();

    return 0;

}



//COUT ERROR
void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                   "%s: %s", msg, error);

    SDL_Quit();
}




//KEY EVENT
void keyPresses()
{

    LTexture gUpTexture;
    gUpTexture.loadFromFile("image/up.png");
    LTexture gDownTexture;
    gDownTexture.loadFromFile("image/down.png");
    LTexture gLeftTexture;
    gLeftTexture.loadFromFile("image/left.png");
    LTexture gRightTexture;
    gRightTexture.loadFromFile("image/right.png");
    LTexture gPressTexture;
    gPressTexture.loadFromFile("image/press.png");



    bool quit = false;
    SDL_Event e;

    LTexture* currentTexture = NULL;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_UP])
            currentTexture = &gUpTexture;

        else if(currentKeyStates[SDL_SCANCODE_DOWN])
            currentTexture = &gDownTexture;

        else if(currentKeyStates[SDL_SCANCODE_LEFT])
            currentTexture = &gLeftTexture;

        else if(currentKeyStates[SDL_SCANCODE_RIGHT])
            currentTexture = &gRightTexture;

        else
            currentTexture = &gPressTexture;


        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        currentTexture->render(0, 0);
        SDL_RenderPresent(gRenderer);
    }
}


//MOUSE EVENT
void mouseEvent()
{
    //Number of buttons
    const int TOTAL_BUTTONS = 4;

    //Button objects
    LButton gButtons[ TOTAL_BUTTONS ];

    //Texture
    gButtonSpriteSheetTexture.loadFromFile("image/button.png");


    for(int i=0; i < BUTTON_SPRITE_TOTAL; i++)
    {
        gSpriteClips[i].x = 0;
        gSpriteClips[i].y = 200*i;
        gSpriteClips[i].h = BUTTON_HEIGHT;
        gSpriteClips[i].w = BUTTON_WIDTH;
    }

    gButtons[0].setPosition(0, 0);
    gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);


    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            for(int i=0; i<TOTAL_BUTTONS; i++)
                gButtons[i].handleEvent(&e);
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        for(int i=0; i<TOTAL_BUTTONS; i++)
        {
            gButtons[i].render();
        }


        SDL_RenderPresent(gRenderer);
    }
}

//TIMER
void printTime()
{

    LTexture gTimeTextTexture;

    //Initialize
    if(TTF_Init() ==-1)
        logErrorAndExit("initTTF", TTF_GetError());

    gFont = TTF_OpenFont("font/lazy.ttf", 28);
    if(gFont == NULL)
        logErrorAndExit("loadFont", TTF_GetError());


    bool quit = false;
    SDL_Event e;
    SDL_Color textColor = {0, 0, 0, 225};
    LTimer timer;
    stringstream timeText;

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
        }

        timeText.str("");
        timeText<<"Seconds since start time "<<(timer.getTicks() / 1000.f);

        gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor);

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        gTimeTextTexture.render((SCREEN_WIDTH - gTimeTextTexture.getWidth()) /2, (SCREEN_HEIGHT - gTimeTextTexture.getHeight()) /2 );
        SDL_RenderPresent(gRenderer);
    }

}


void motion()
{
    gDotTexture.loadFromFile("image/dot.bmp");
    LTexture gBGTexture;
    bool quit = false;
    SDL_Event e;
    Dot dot(Dot::DOT_WIDTH / 2, Dot::DOT_HEIGHT / 2);
    Dot otherDot( SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 );

    SDL_Rect wall;
    wall.x = 300;
    wall.y = 40;
    wall.w = 40;
    wall.h = 400;

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
                quit = true;

            dot.handleEvent(e);
        }

        dot.Move(wall, otherDot.getCollider());



        //take center as when the background scroll
        camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
        camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
        if(camera.x < 0)
            camera.x = 0;
        if(camera.y < 0)
            camera.y = 0;
        if(camera.x > LEVEL_WIDTH - camera.w)
            camera.x = LEVEL_WIDTH - camera.w;
        if(camera.y > LEVEL_HEIGHT - camera.h)
            camera.y = LEVEL_HEIGHT - camera.h;


        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );


        gBGTexture.loadFromFile("image/bg2.png");
        gBGTexture.render(0, 0);


        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderFillRect( gRenderer, &wall );


        dot.render(camera.x, camera.y);
        otherDot.render(camera.x, camera.y);

        SDL_RenderPresent(gRenderer);
    }
}



//RELEASE MEMORY
void close()
{
    SDL_DestroyRenderer(gRenderer);
    gWindow.free();

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}





