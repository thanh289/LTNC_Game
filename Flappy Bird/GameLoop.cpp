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
	GameOver.setSrc(0, 0, 192, 42);
	GameOver.setDest((SCREEN_WIDTH-192)/2, (SCREEN_HEIGHT-42)/4, 192, 42);
	ScoreBoard.setSrc(0, 0, 113, 57);
	ScoreBoard.setDest((SCREEN_WIDTH-339)/2, 220, 339, 171);
	New.setSrc(0, 0, 16, 7);
	New.setDest(345, 310, 32, 14);
	OkButton.setSrc(0, 0, 80, 28);
	OkButton.setDest((SCREEN_WIDTH-80)/2, 400, 80, 28);
    CopperIcon.setSrc(0, 0, 66, 66);
    CopperIcon.setDest(170, 280, 66, 66);
    SilverIcon.setSrc(0, 0, 66, 66);
    SilverIcon.setDest(170, 280, 66, 66);
    GoldIcon.setSrc(0, 0, 66, 66);
    GoldIcon.setDest(170, 280, 66, 66);

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
        numberCount[i].setSrc(0, 0, 24, 36);
        numberCur[i].setSrc(0, 0, 24, 36);
        numberBest[i].setSrc(0, 0, 24, 36);
    }

}

bool GameLoop::getGameState()
{
	return GameState;
}

void GameLoop::PlayAgain()
{
    guide.setSrc(0, 0, 184, 267);
	guide.setDest((SCREEN_WIDTH-184)/2, (SCREEN_HEIGHT-267)/2, 184, 267);
	GameOver.setSrc(0, 0, 192, 42);
	GameOver.setDest((SCREEN_WIDTH-192)/2, (SCREEN_HEIGHT-42)/4, 192, 42);
    ScoreBoard.setSrc(0, 0, 113, 57);
	ScoreBoard.setDest((SCREEN_WIDTH-339)/2, 220, 339, 171);

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
        numberCount[i].setSrc(0, 0, 24, 36);
        numberCount[i].setDest(20, 20, 24, 36);
    }

    CheckNew = 0;
}


void GameLoop::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("FLAPPY BIRD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
            GameOver.CreateTexture("image/gameover.png", renderer);
            ScoreBoard.CreateTexture("image/score-board.png", renderer);
            New.CreateTexture("image/new.png", renderer);
            AliveBird.CreateTexture("image/yellowbird1.png", renderer);
            AliveBird.CreateTexture1("image/yellowbird2.png", renderer);
            AliveBird.CreateTexture2("image/yellowbird3.png", renderer);
            DieBird.CreateTexture("image/yellowbird4.png", renderer);
            Back.CreateTexture("image/background.png", renderer);
            for(int i=0; i<8; i++)
                ground[i].CreateTexture("image/base.png", renderer);
            for(int i=0; i<8; i++)
                ColUp[i].CreateTexture("image/pipe-green-up.png", renderer);
            for(int i=0; i<8; i++)
                ColDown[i].CreateTexture("image/pipe-green-down.png", renderer);

            numberCount[0].CreateTexture("image/0.png", renderer);
            numberCount[1].CreateTexture("image/1.png", renderer);
            numberCount[2].CreateTexture("image/2.png", renderer);
            numberCount[3].CreateTexture("image/3.png", renderer);
            numberCount[4].CreateTexture("image/4.png", renderer);
            numberCount[5].CreateTexture("image/5.png", renderer);
            numberCount[6].CreateTexture("image/6.png", renderer);
            numberCount[7].CreateTexture("image/7.png", renderer);
            numberCount[8].CreateTexture("image/8.png", renderer);
            numberCount[9].CreateTexture("image/9.png", renderer);

            numberCur[0].CreateTexture("image/0.png", renderer);
            numberCur[1].CreateTexture("image/1.png", renderer);
            numberCur[2].CreateTexture("image/2.png", renderer);
            numberCur[3].CreateTexture("image/3.png", renderer);
            numberCur[4].CreateTexture("image/4.png", renderer);
            numberCur[5].CreateTexture("image/5.png", renderer);
            numberCur[6].CreateTexture("image/6.png", renderer);
            numberCur[7].CreateTexture("image/7.png", renderer);
            numberCur[8].CreateTexture("image/8.png", renderer);
            numberCur[9].CreateTexture("image/9.png", renderer);


            numberBest[0].CreateTexture("image/0.png", renderer);
            numberBest[1].CreateTexture("image/1.png", renderer);
            numberBest[2].CreateTexture("image/2.png", renderer);
            numberBest[3].CreateTexture("image/3.png", renderer);
            numberBest[4].CreateTexture("image/4.png", renderer);
            numberBest[5].CreateTexture("image/5.png", renderer);
            numberBest[6].CreateTexture("image/6.png", renderer);
            numberBest[7].CreateTexture("image/7.png", renderer);
            numberBest[8].CreateTexture("image/8.png", renderer);
            numberBest[9].CreateTexture("image/9.png", renderer);



            OkButton.CreateTexture("image/ok.png", renderer);
            CopperIcon.CreateTexture("image/copper.png", renderer);
            SilverIcon.CreateTexture("image/silver.png", renderer);
            GoldIcon.CreateTexture("image/gold.png", renderer);
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

    if(event1.type == SDL_MOUSEBUTTONDOWN || event1.key.keysym.sym == SDLK_SPACE)
    {
            Start =true;
            AliveBird.Jump();
    }
    AliveBird.Gravity();


    for(int i=0; i<8; i++)
    {
        ground[i].Move();
            if(ground[i].getDest().x < -GROUND_WIDTH)
                ground[i].SetGround(ground[(i+7)%8].getDest().x + GROUND_WIDTH - 50);
    }


    if(ColUp[CurCol].getDest().x <= 60)
    {
        CurScore++;
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

    if(Die)
    {
        Start = false;
        if(OkButton.HandleEvent(&event1) || event1.key.keysym.sym  == SDLK_RETURN)
        {
            PlayAgain();
            Die = false;
            AliveBird.Revive();
            CurScore = 0;
            CurCol = 0;
            for(int j=0; j<8; j++)
            {
                ground[j].Continue();
                ColUp[j].Continue();
                ColDown[j].Continue();
            }
        }
    }

}


void GameLoop::Render()
{
	SDL_RenderClear(renderer);
	Back.NormalRender(renderer);

    if(!Start)
        if(!Die)
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
        if(CurScore<10)
        {
            int c = CurScore;
            numberCount[c].setDest(20, 20, 24, 36);
            numberCount[c].AdvanceRender(renderer, numberCount[c].getSrc(), numberCount[c].getDest());
        }
        else
        {
            int tem = CurScore;
            vector<int> digits;
            while(tem>0)
            {
                digits.push_back(tem%10);
                tem/=10;
            }
            int n = digits.size();
            for(int i=n-1; i>=0; i--)
            {
                int d = digits[i];
                numberCount[d].setDest(20 + 24*(n-i-1), 20, 24, 36);
                numberCount[d].AdvanceRender(renderer, numberCount[d].getSrc(), numberCount[d].getDest());
            }
        }

    }


	if(Die)
    {
        GameOver.AdvanceRender(renderer, GameOver.getSrc(), GameOver.getDest());
        DieBird.DieRender(renderer, AliveBird.getSrc(), AliveBird.getDest());
        ScoreBoard.AdvanceRender(renderer, ScoreBoard.getSrc(), ScoreBoard.getDest());
        OkButton.Render(renderer, OkButton.getSrc(), OkButton.getDest());
        if(CurScore >= 1 && CurScore < 10)
            CopperIcon.AdvanceRender(renderer, CopperIcon.getSrc(), CopperIcon.getDest());
        else if(CurScore >= 10 && CurScore < 50)
            SilverIcon.AdvanceRender(renderer, SilverIcon.getSrc(), SilverIcon.getDest());
        else if(CurScore >= 50)
            GoldIcon.AdvanceRender(renderer, GoldIcon.getSrc(), GoldIcon.getDest());


        //show Curscore in board
        if(CurScore<10)
        {
            int c = CurScore;
            numberCur[c].setDest(415, 270, 20, 30);
            numberCur[c].AdvanceRender(renderer, numberCur[c].getSrc(), numberCur[c].getDest());
        }
        else
        {
            int tem = CurScore;
            vector<int> digits;
            while(tem>0)
            {
                digits.push_back(tem%10);
                tem/=10;
            }
            int n = digits.size();
            for(int i=0; i<n; i++)
            {
                int d = digits[i];
                numberCur[d].setDest(415 - 20*i, 270, 20, 30);
                numberCur[d].AdvanceRender(renderer, numberCur[d].getSrc(), numberCur[d].getDest());
            }
        }


        //show BestScore in board
        if(BestScore < CurScore){
            CheckNew = 1;
            BestScore = CurScore;
        }

        if(CheckNew)
            New.AdvanceRender(renderer, New.getSrc(), New.getDest());

        if(BestScore<10)
        {
            int b = BestScore;
            numberBest[b].setDest(415, 330, 20, 30);
            numberBest[b].AdvanceRender(renderer, numberBest[b].getSrc(), numberBest[b].getDest());
        }
        else
        {
            int tem = BestScore;
            vector<int> digits;
            while(tem>0)
            {
                digits.push_back(tem%10);
                tem/=10;
            }
            int n = digits.size();
            for(int i=0; i<n; i++)
            {
                numberBest[digits[i]].setDest(415 - 20*i, 330, 24, 36);
                numberBest[digits[i]].AdvanceRender(renderer, numberBest[digits[i]].getSrc(), numberBest[digits[i]].getDest());
            }
        }
    }

	SDL_RenderPresent(renderer);
}



void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}



void hello();
