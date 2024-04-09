
#include "Button.h"
#include "SDL.h"

void Button::Render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}



bool Button::HandleEvent( SDL_Event* e )
{
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
		SDL_GetMouseState( &x, &y );

		bool inside = true;

		if( x < getDest().x )
			inside = false;
		else if( x > getDest().x + BUTTON_WIDTH )
			inside = false;
		else if( y < getDest().y )
			inside = false;
		else if( y > getDest().y + BUTTON_HEIGHT )
			inside = false;



		if(inside)
		{
		    if(e->type == SDL_MOUSEBUTTONDOWN)
                return true;
		}
	}

	return false;
}
