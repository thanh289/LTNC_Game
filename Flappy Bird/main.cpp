#include <iostream>
#include "GameLoop.h"
using namespace std;

GameLoop* g1 = new GameLoop();

int main(int argc, char** argv)
{
    cout<<"Flappy Bird"<<endl;
	g1->Initialize();
	while (g1->getGameState())
	{
		g1->Event();
		g1->Render();

	}
	g1->Clear();

	return 0;
}
