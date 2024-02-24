#include <bits/stdc++.h>
#include"GameLoop.h"

using namespace std;


GameLoop::GameLoop()
{
	window = NULL;
	renderer = NULL;
	GameState = false;
	guide.setSrc(0, 0, 184, 267);
	guide.setDest((SCREEN_WIDTH-184)/2, (SCREEN_HEIGHT-267)/2, 184, 267);
	d.setSrc(0, 0, 192, 42);
	d.setDest((SCREEN_WIDTH-192)/2, (SCREEN_HEIGHT-42)/2, 192, 42);

	AliveBird.setSrc(0, 0, 34, 24);
	AliveBird.setDest(50, SCREEN_HEIGHT/2, 34, 24);
	for(int i=0; i<8; i++)
        ground[i].SetGround(i*GROUND_WIDTH - 50);
	for(int i=0; i<8; i++)
    {
        YCol = rand() % 150;
        ColUp[i].SetPos((SCREEN_WIDTH + 170*i+400), -YCol);
        ColDown[i].SetPos((SCREEN_WIDTH + 170*i+400), (-YCol + COL_HEIGHT + 100));
    }
    for(int i=0; i<10; i++)
    {
        number[i].setSrc(0, 0, 24, 36);
        number[i].setDest(20, 20, 24, 36);
    }

}

bool GameLoop::getGameState()
{
	return GameState;
}

void GameLoop::Intialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(window == NULL)
    {
        cout<<"Failed to create window! Error: "<<SDL_GetError();
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == NULL)
            cout<<"Failed to create renderer! Error: "<<SDL_GetError();
        else
        {
            GameState = true;

            guide.CreateTexture("image/message.png", renderer);
            d.CreateTexture("image/gameover.png", renderer);
            AliveBird.CreateTexture("image/yellowbird1.png", renderer);
            AliveBird.CreateTexture1("image/yellowbird2.png", renderer);
            AliveBird.CreateTexture2("image/yellowbird3.png", renderer);
            DieBird.CreateTexture("image/yellowbird4.png", renderer);
            b.CreateTexture("image/background.png", renderer);
            for(int i=0; i<8; i++)
                ground[i].CreateTexture("image/base.png", renderer);
            for(int i=0; i<8; i++)
                ColUp[i].CreateTexture("image/pipe-green-up.png", renderer);
            for(int i=0; i<8; i++)
                ColDown[i].CreateTexture("image/pipe-green-down.png", renderer);

            number[0].CreateTexture("image/0.png", renderer);
            number[1].CreateTexture("image/1.png", renderer);
            number[2].CreateTexture("image/2.png", renderer);
            number[3].CreateTexture("image/3.png", renderer);
            number[4].CreateTexture("image/4.png", renderer);
            number[5].CreateTexture("image/5.png", renderer);
            number[6].CreateTexture("image/6.png", renderer);
            number[7].CreateTexture("image/7.png", renderer);
            number[8].CreateTexture("image/8.png", renderer);
            number[9].CreateTexture("image/9.png", renderer);

        }
    }
}


void GameLoop::Event()
{

    SDL_PollEvent(&event1);
	if (event1.type == SDL_QUIT)
	{
		GameState = false;
	}

    if(event1.type == SDL_MOUSEBUTTONDOWN || event1.key.keysym.sym == SDLK_j)
    {
        Start =true;
        AliveBird.Jump();
    }
    AliveBird.Gravity();


    for(int i=0; i<8; i++)
    {
        ground[i].Move();
            if(ground[i].getDest().x < -GROUND_WIDTH)
                ground[i].SetGround(ground[(i+2)%3].getDest().x + GROUND_WIDTH - 50);
    }


    if(ColUp[CurCol].getDest().x <= 60)
    {
        Score++;
        CurCol++;
        if(CurCol == 8) CurCol = 0;
    }


    if(Start)
    {
        for(int i=0; i<8; i++)
        {
            ColUp[i].MoveUp();
            ColDown[i].MoveDown();
            if(ColUp[i].getDest().x < -COL_WIDTH)
            {
                YCol = rand() % 150;
                ColUp[i].SetPos(ColUp[(i+7)%8].getDest().x + 170, -YCol);
                ColDown[i].SetPos(ColDown[(i+7)%8].getDest().x + 170, -YCol + COL_HEIGHT + 100);
            }



            if(AliveBird.GetCollision(ColUp[i].getDest(), COL_WIDTH, COL_HEIGHT) || AliveBird.GetCollision(ColDown[i].getDest(), COL_WIDTH, COL_HEIGHT) || AliveBird.GetCollision(ground[i].getDest(), GROUND_WIDTH, GROUND_HEIGHT))
            {
                AliveBird.Die();
                Die = true;
                for(int j=0; j<8; j++)
                {
                    ground[j].Stop();
                    ColUp[j].Stop();
                    ColDown[j].Stop();
                }
                break;
            }
        }
    }

}


void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	b.NormalRender(renderer);

    if(!Start)
        guide.AdvanceRender(renderer, guide.getSrc(), guide.getDest());

    if(!Die)
        AliveBird.AliveRender(renderer, AliveBird.getSrc(), AliveBird.getDest());

    for(int i=0; i<8; i++)
    {
        ColUp[i].CollumnRender(renderer, ColUp[i].getSrc(), ColUp[i].getDest());
        ColDown[i].CollumnRender(renderer, ColDown[i].getSrc(), ColDown[i].getDest());
    }
    for(int i=0; i<8; i++)
    {
        ground[i].AdvanceRender(renderer, ground[i].getSrc(), ground[i].getDest());
    }

    if(Start)
    {
        if(Score<10)
        {
            number[Score].AdvanceRender(renderer, number[Score].getSrc(), number[Score].getDest());
        }
        else
        {
            int tem = Score;
            vector<int> digits;
            while(tem>0)
            {
                digits.push_back(tem%10);
                tem/=10;
            }
            int n = digits.size();
            for(int i=n-1; i>=0; i--)
            {
                number[digits[i]].setDest(20 + 24*(n-i-1), 20, 24, 36);
                number[digits[i]].AdvanceRender(renderer, number[digits[i]].getSrc(), number[digits[i]].getDest());
            }

        }

    }

	if(Die)
    {
        d.AdvanceRender(renderer, d.getSrc(), d.getDest());
        DieBird.DieRender(renderer, AliveBird.getSrc(), AliveBird.getDest());
    }

	SDL_RenderPresent(renderer);
}


void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}




