#pragma once
#include <SDL.h>

class SdlSetup
{
public:
	SdlSetup(bool* quit, int s_width, int s_height); //ctor, takesthe game quit variable, and the screen width and height
	~SdlSetup();

	//Getters

	SDL_Renderer* GetRenderer() const;
	SDL_Event* GetMainEvent() const;
	SDL_Window* GetWindow() const;

	void Begin() const; //Game loop start function, prerpare renderer and get main event
	void End() const; //Game loop end function, clear renderer

private:
	SDL_Window* _window; //window where the game will be displayed
	SDL_Renderer* _renderer; //renderer which will draw images and other graphics to the screen
	SDL_Event* _mainEvent; //to keep track of keyboard, mouse and other events
};

