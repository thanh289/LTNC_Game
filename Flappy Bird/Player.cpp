#include "Player.h"


void Player::DieRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(ren, getTexture(), &src, &dest);
}

void Player::AliveRender(SDL_Renderer* ren, SDL_Rect src, SDL_Rect dest)
{
    animationTimer++;
	if (animationTimer < 16)
	{
		SDL_RenderCopy(ren, getTexture(), &src, &dest);
	}
	else if (animationTimer >= 16 && animationTimer <= 32)
	{
		SDL_RenderCopy(ren, Tex1, &src, &dest);
	}
	else if (animationTimer > 32)
	{
		SDL_RenderCopy(ren, Tex2, &src, &dest);
	}
	if (animationTimer > 48)
	{
		animationTimer = 0;
	}
}


void Player::Gravity()
{
	if (JumpState())
	{
		accelerator += 0.2;
		Ypos += gravity + accelerator + jumpHeight;
		setDest(50, Ypos, 34, 24);

	}

}

void Player::Jump()
{
    accelerator = 0;
    inJump = true;
}


void Player::Die()
{
    inJump = false;
    gravity = 0;
    jumpHeight = 0;
    accelerator = 0;
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




bool Player::JumpState()
{
	return inJump;
}

void Player::CreateTexture1(const char* address, SDL_Renderer* ren)
{
	Tex1 = TextureManager::Texture(address, ren);
}

void Player::CreateTexture2(const char* address, SDL_Renderer* ren)
{
	Tex2 = TextureManager::Texture(address, ren);
}
