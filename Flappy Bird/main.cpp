#include <iostream>
#include "GameLoop.h"
#include "Music.h"
using namespace std;

GameLoop* g1 = new GameLoop();
Music themeSong;
int main(int argc, char** argv)
{
    const int fps = 60;
    const int delay_time = 1000/fps;

    Uint64 Start;
    Uint64 frameTime;

	g1->Initialize();
	g1->PlayThemeSong();
	while (g1->getGameState())
	{

		g1->Event();
		g1->RenderAll();

		frameTime = SDL_GetTicks() - Start;
		if(frameTime <  delay_time)
        {
            SDL_Delay(delay_time - frameTime);
        }

	}
	g1->Clear();

	return 0;
}
