
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
	ScoreBoard.setSrc(0, 0, 250, 128);
	ScoreBoard.setDest((SCREEN_WIDTH-339)/2, 220, 339, 171);
	PauseBoard.setSrc(0, 0, 250, 128);
	PauseBoard.setDest((SCREEN_WIDTH-339)/2, 220, 339, 171);
	New.setSrc(0, 0, 16, 7);
	New.setDest(345, 310, 32, 14);
	OkButton.setSrc(0, 0, 80, 28);
	OkButton.setDest((SCREEN_WIDTH-80)/2, 400, 80, 28);
	PauseButton.setSrc(0, 0, 26, 28);
	PauseButton.setDest(SCREEN_WIDTH-40, 15, 26, 28);
	SoundIconOn.setSrc(0, 0, 32, 24);
	SoundIconOn.setDest(210, 270, 32, 24);
	SoundIconOff.setSrc(0, 0, 32, 24);
	SoundIconOff.setDest(205, 270, 32, 24);
	BgTheme.setSrc(0, 0, 55, 58);
	BgTheme.setDest(210, 330, 32, 32);
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
        YCol = rand() % 200;
        ColUp[i].SetPos((SCREEN_WIDTH + 170*i+100), -YCol);
        ColDown[i].SetPos((SCREEN_WIDTH + 170*i+100), (-YCol + COL_HEIGHT + 100));
    }
    for(int i=0; i<10; i++)
    {
        numberCount[i].setSrc(0, 0, 24, 36);
        numberCur[i].setSrc(0, 0, 24, 36);
        numberBest[i].setSrc(0, 0, 24, 36);
    }

    Back[0].setSrc(0, 0, 800, 640);
    Back[0].setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Back[1].setSrc(0, 0, 640, 600);
    Back[1].setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Back[2].setSrc(0, 0, 600, 504);
    Back[2].setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Back[3].setSrc(0, 0, 1153, 1080);
    Back[3].setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Back[4].setSrc(0, 0, 820, 640);
    Back[4].setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


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
        ColUp[i].SetPos((SCREEN_WIDTH + 170*i+100), -YCol);
        ColDown[i].SetPos((SCREEN_WIDTH + 170*i+100), (-YCol + COL_HEIGHT + 100));
    }

    for(int i=0; i<10; i++)
    {
        numberCount[i].setSrc(0, 0, 24, 36);
        numberCount[i].setDest(20, 20, 24, 36);
    }

    SongState = 0;
    CheckNew = 0;
}


bool GameLoop::getGameState()
{
	return GameState;
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
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
            cout<<"Failed to init mixer! Error: "<<Mix_GetError();
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
                PauseBoard.CreateTexture("image/pauseTab.png", renderer);
                New.CreateTexture("image/new.png", renderer);
                AliveBird.CreateTexture("image/yellowbird1.png", renderer);
                AliveBird.CreateTexture1("image/yellowbird2.png", renderer);
                AliveBird.CreateTexture2("image/yellowbird3.png", renderer);

                Back[0].CreateTexture("image/background.png", renderer);
                Back[1].CreateTexture("image/background night.jpg", renderer);
                Back[2].CreateTexture("image/background cloudy.png", renderer);
                Back[3].CreateTexture("image/background sunshine.jpg", renderer);
                Back[4].CreateTexture("image/background tree.jpg", renderer);

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
                PauseButton.CreateTexture("image/pause.png", renderer);
                SoundIconOn.CreateTexture("image/SoundOn.png", renderer);
                SoundIconOff.CreateTexture("image/SoundOff.png", renderer);
                BgTheme.CreateTexture("image/change theme.jpg", renderer);
                CopperIcon.CreateTexture("image/copper.png", renderer);
                SilverIcon.CreateTexture("image/silver.png", renderer);
                GoldIcon.CreateTexture("image/gold.png", renderer);

                flyMu.loadChunk("sound/sfx_wing.wav");
                getHit.loadChunk("sound/sfx_hit.wav");
                getPoint.loadChunk("sound/sfx_point.wav");
                click.loadChunk("sound/sfx_click.wav");
                StartSong.loadMusic("sound/Bit_Adventure.mp3");
                PlaySong.loadMusic("sound/8_Bit_Surf.mp3");
            }
        }
    }
}


void GameLoop::SaveBestScore()
{
    fstream file("score.txt");
    file<<BestScore;
    file.close();
}
void GameLoop::TakeBestScore()
{
    fstream file("score.txt");
    file>>BestScore;
    file.close();
}




void GameLoop::Event()
{

    TakeBestScore();
    if(SongState == 0)
    {
        SongState++;
        StartSong.playMusic();
    }
    if(SongState == 2)
    {
        PlaySong.playMusic();
    }

    if(!SoundOn || Pause || Die)
        PlaySong.pauseMusic();
    else PlaySong.resumeMusic();


    SDL_PollEvent(&event1);
	if (event1.type == SDL_QUIT)
	{
		GameState = false;
	}

    if((event1.type == SDL_MOUSEBUTTONDOWN || event1.key.keysym.sym == SDLK_SPACE) && !PauseButton.HandleEvent(&event1) && !Die)
    {

            if(!Pause)
            {
                Start =true;
                SongState++;
            }
            if(Start) AliveBird.Jump();
            if(SoundOn && !Pause && !Die) flyMu.playChunk();
    }
    if(Start) AliveBird.Gravity();


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
        if(SoundOn) getPoint.playChunk();
        if(CurCol == 8) CurCol = 0;
    }
    if(BestScore < CurScore){
        CheckNew = 1;
        BestScore = CurScore;
        SaveBestScore();
    }

    if(CurScore>=10)
    {
        for(int i=0; i<8; i++)
        {
            int t = ColUp[i].getDest().y;
            if(t == 0)
                ColMoveup = true;
            else if(t == -149)
                ColMoveup = false;

            if(ColMoveup)
            {
//                if(i%2)
                {
                    ColUp[i].MoveUp();
                    ColDown[i].MoveUp();
                }

            }
            else
            {
                if(i%2)
                {
                    ColUp[i].MoveDown();
                    ColDown[i].MoveDown();
                }
            }
        }
    }

    if(Start)
    {
        for(int i=0; i<8; i++)
        {
            ColUp[i].ColMove();
            ColDown[i].ColMove();
            if(ColUp[i].getDest().x < -COL_WIDTH)
            {
                YCol = rand() % 150;
                ColUp[i].SetPos(ColUp[(i+7)%8].getDest().x + 170, -YCol);
                ColDown[i].SetPos(ColDown[(i+7)%8].getDest().x + 170, -YCol + COL_HEIGHT + 100);
            }


            if(AliveBird.GetCollision(ColUp[i].getDest(), COL_WIDTH, COL_HEIGHT) || AliveBird.GetCollision(ColDown[i].getDest(), COL_WIDTH, COL_HEIGHT) || AliveBird.GetCollision(ground[i].getDest(), GROUND_WIDTH, GROUND_HEIGHT))
            {
                AliveBird.Die();
                if(SoundOn && !Die)getHit.playChunk();
                PlaySong.pauseMusic();
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


    if((PauseButton.HandleEvent(&event1) || event1.key.keysym.sym  == SDLK_m) && !Pause && !Die)
    {
        Pause = true;
        PlaySong.pauseMusic();
        for(int i=0; i<8; i++)
        {
            ground[i].Stop();
            ColUp[i].Stop();
            ColDown[i].Stop();
        }
        AliveBird.Stop();
    }
    else if((PauseButton.HandleEvent(&event1) || OkButton.HandleEvent(&event1) || event1.key.keysym.sym  == SDLK_m) && Pause)
    {
        Pause = false;
        PlaySong.resumeMusic();
        for(int i=0; i<8; i++)
        {
            ground[i].Continue();
            ColUp[i].Continue();
            ColDown[i].Continue();
        }
        AliveBird.Continue();
    }

    if(Pause)
    {
        if(SoundIconOn.HandleEvent(&event1))
        {
            click.playChunk();
            if(SoundOn)
                SoundOn = false;
            else
                SoundOn = true;
        }

        if(BgTheme.HandleEvent(&event1))
        {
            click.playChunk();
            if(CurBack==4) CurBack = 0;
            else CurBack++;
        }
    }



    if(Die)
    {
        Start = false;
        AliveBird.Die();
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



void GameLoop::RenderBestCurNum()
{

    //show Curscore in board
    if(CurScore<10)
    {
        int c = CurScore;
        numberCur[c].setDest(415, 270, 20, 30);
        numberCur[c].Render(renderer);
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
            numberCur[d].Render(renderer);
        }
    }


    //show BestScore in board
    if(CheckNew)
        New.Render(renderer);
    if(BestScore<10)
    {
        int b = BestScore;
        numberBest[b].setDest(415, 330, 20, 30);
        numberBest[b].Render(renderer);
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
            numberBest[digits[i]].setDest(415 - 20*i, 330, 20, 30);
            numberBest[digits[i]].Render(renderer);
        }
    }
}



void GameLoop::RenderAll()
{

	SDL_RenderClear(renderer);
	Back[CurBack].Render(renderer);

    if(!Start && !Pause)
        if(!Die)
            guide.Render(renderer);

    if(!Die && !Pause)
        AliveBird.AliveRender(renderer);

    for(int i=0; i<8; i++)
    {
        ColUp[i].CollumnRender(renderer);
        ColDown[i].CollumnRender(renderer);
    }
    for(int i=0; i<8; i++)
    {
        ground[i].Render(renderer);
    }

    PauseButton.Render(renderer);

    if(Start)
    {

        if(CurScore<10)
        {
            int c = CurScore;
            numberCount[c].setDest(20, 20, 24, 36);
            numberCount[c].Render(renderer);
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
                numberCount[d].Render(renderer);
            }
        }

    }

    if(Pause)
    {
        PauseBoard.Render(renderer);
        PauseButton.Render(renderer);
        OkButton.Render(renderer);
        BgTheme.Render(renderer);
        AliveBird.DieRender(renderer);
        RenderBestCurNum();
        if(SoundOn)
            SoundIconOn.Render(renderer);
        if(!SoundOn)
            SoundIconOff.Render(renderer);
    }

	if(Die)
    {
        GameOver.Render(renderer);
        AliveBird.DieRender(renderer);
        ScoreBoard.Render(renderer);
        OkButton.Render(renderer);
        if(CurScore >= 1 && CurScore < 10)
            CopperIcon.Render(renderer);
        else if(CurScore >= 10 && CurScore < 50)
            SilverIcon.Render(renderer);
        else if(CurScore >= 50)
            GoldIcon.Render(renderer);

        RenderBestCurNum();
    }

	SDL_RenderPresent(renderer);
}



void GameLoop::Clear()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}



