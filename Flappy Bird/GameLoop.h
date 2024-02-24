#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include "Player.h"
#include "Object.h"
#include "Background.h"
#include "Col.h"

class GameLoop
{
private:
    const int SCREEN_HEIGHT = 640;
	const int SCREEN_WIDTH = 600;
	const int GROUND_HEIGHT = 112;
	const int GROUND_WIDTH = 336;
	const int COL_HEIGHT = 320;
	const int COL_WIDTH = 52;
	Player AliveBird;
	Player DieBird;
	Background b;
	Background guide;
	Background d;
	Background number[10];
	Background ground[8];
    Collumn ColUp[8];
    Collumn ColDown[8];
	int XGround = 0;
	int YCol;
	int Score = 0;
	int CurCol = 0;
	bool GameState;
	bool Start = false;
	bool Die = false;
	SDL_Window* window;
	SDL_Event event1;
	SDL_Renderer* renderer;
public:
	GameLoop();
	bool getGameState();
	void Intialize();
	void Event();
	void Render();
	void Clear();
};
