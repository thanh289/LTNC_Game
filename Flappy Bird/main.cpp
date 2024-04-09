#include <iostream>
#include "GameLoop.h"
#include "Music.h"
using namespace std;

GameLoop* g1 = new GameLoop();
Music themeSong;
int main(int argc, char** argv)
{

    cout<<"Flappy Bird"<<endl;
	g1->Initialize();
	g1->PlayThemeSong();
	while (g1->getGameState())
	{
//	    int x, y;
//      SDL_GetMouseState( &x, &y );
//      cout<<x<<" "<<y<<endl;
		g1->Event();
		g1->RenderAll();

	}
	g1->Clear();

	return 0;
}
