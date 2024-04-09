#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Object.h"
#include "Background.h"
#include "Col.h"
#include "Button.h"
#include "Music.h"
using namespace std;

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
	Background Back[5];
	Background guide;
	Background GameOver;
	Background ScoreBoard;
	Background PauseBoard;
	Background New;
	Background numberCount[10];
	Background numberCur[10];
	Background numberBest[10];
	Background ground[8];
	Background CopperIcon;
	Background SilverIcon;
	Background GoldIcon;
    Collumn ColUp[8];
    Collumn ColDown[8];
    Button OkButton;
    Button PauseButton;
    Button SoundIconOn;
    Button SoundIconOff;
    Button BgTheme;
    Music flyMu;
    Music getHit;
    Music getPoint;
    Music click;
    Music themeSong;
	int XGround = 0;
	int YCol;
	int CurScore = 0;
	int BestScore = 0;
	int CheckNew = 0;
	int CurCol = 0;
	int CurBack = 0;
	bool GameState;
	bool Start = false;
	bool Pause = false;
	bool Die = false;
	bool ColMoveup = true;
	bool SoundOn = true;
	SDL_Window* window;
	SDL_Event event1;
	SDL_Renderer* renderer;
public:
	GameLoop();
	bool getGameState();
	void PlayThemeSong();
	void SaveBestScore();
	void TakeBestScore();
	void RenderBestCurNum();
	void PlayAgain();
	void Initialize();
	void Event();
	void RenderAll();
	void Clear();
};
