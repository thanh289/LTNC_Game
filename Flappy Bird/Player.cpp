#include "Player.h"


void Player::DieRender(SDL_Renderer* ren)
{
    SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
}

void Player::AliveRender(SDL_Renderer* ren)
{
    animationTimer++;
	if (animationTimer < 20)
	{
		    SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer >= 20 && animationTimer <= 40)
	{
		    SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);

	}
	else if (animationTimer > 40)
	{
		    SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), angle, NULL, SDL_FLIP_NONE);

	}
	if (animationTimer > 60)
	{
		animationTimer = 0;
	}
}


void Player::Gravity()
{
	if (inJump && !Pause)
	{
		accelerator1 += 0.2;
		Ypos += accelerator1 + jumpHeight;
		setDest(50, Ypos, 34, 24);
        angle += 2;
		if(Ypos<0){
            Ypos = 0;
            Ypos += 2;
		}
	}

	if (angle >= 45)
		angle = 45;

}

void Player::Jump()
{
        accelerator1 = 0;
        angle = -45;
        inJump = true;
}


void Player::Die()
{
    inJump = false;
    Pause = true;
    if(Ypos < 500)
    {
        accelerator2 += 0.2;
        Ypos += accelerator2;
        setDest(50, Ypos, 34, 24);
    }
    if(angle < 90)
        angle += 3;

}

void Player::Stop()
{
	Pause = true;
}

void Player::Continue()
{
	Pause = false;
}

void Player::Revive()
{
    Pause = false;
    jumpHeight = -4;
    Ypos = 320;
    accelerator2 = 0;
    angle = 0;
}



bool Player::GetCollision(SDL_Rect Col, int ob_W, int ob_H)
{
    SDL_Rect recA = getDest();
    SDL_Rect recB = Col;

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = recA.x;
    rightA = recA.x + 34;
    topA = recA.y;
    bottomA = recA.y + 24;

    leftB = recB.x;
    rightB = recB.x + ob_W;
    topB = recB.y;
    bottomB = recB.y + ob_H;

    if( bottomA <= topB)
        return false;

    if( topA >= bottomB)
        return false;

    if( rightA <= leftB)
        return false;

    if( leftA >= rightB )
        return false;

    return true;
}



void Player::CreateTexture1(const char* address, SDL_Renderer* ren)
{
    SDL_Surface* surface;
	surface = IMG_Load(address);
	Tex1 = SDL_CreateTextureFromSurface(ren, surface);
}

void Player::CreateTexture2(const char* address, SDL_Renderer* ren)
{
	SDL_Surface* surface;
	surface = IMG_Load(address);
	Tex2 = SDL_CreateTextureFromSurface(ren, surface);
}
