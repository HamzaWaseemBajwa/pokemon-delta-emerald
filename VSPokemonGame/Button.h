#pragma once
#include <SDL.h>
#include "SdlSetup.h"
#include "PokemonMove.h"

class Button
{
public:
	Button(SdlSetup* passed_setup, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b); //button contructor, with color 
	Button(SdlSetup* passed_setup, int x, int y, int w, int h); //button construtor, without color

	void Draw() const; //Draw simple button
	void Draw(PokemonMove* passed_move, int pp); //Draw button for move selection 
	void ClickedAnimation() const; //Clicking animation
	bool Clicked(const int x, const int y) const; //Boolean if clicked

	~Button();
private:
	SdlSetup* _sdlSetup; //setup where the button must be displayed
	SDL_Rect _buttonRect; //rect for button dimensions
	SDL_Color _color; //button color
};

