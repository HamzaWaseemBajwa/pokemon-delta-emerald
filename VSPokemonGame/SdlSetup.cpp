#include "SdlSetup.h"
#include <iostream>
#include <SDL.h>


SdlSetup::SdlSetup(bool* quit, const int w_width, const int w_height)
{
	SDL_Init(SDL_INIT_VIDEO);
	_window = SDL_CreateWindow("Pokemon: Delta Emerald", 50, 50, w_width, w_height, SDL_WINDOW_SHOWN);
	if (_window == nullptr) 
	{
		std::cout << "Window couldn't be made" << '\n';
		*quit = true;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	_mainEvent = new SDL_Event();
}


SdlSetup::~SdlSetup()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete _mainEvent;
}

SDL_Renderer* SdlSetup::GetRenderer() const
{
	return _renderer;
}

SDL_Event* SdlSetup::GetMainEvent() const
{
	return _mainEvent;
}

SDL_Window* SdlSetup::GetWindow() const
{
	return _window;
}

void SdlSetup::Begin() const
{
	SDL_PollEvent(_mainEvent); //get main event
	SDL_RenderClear(_renderer); //prepare renderer
}

void SdlSetup::End() const
{
	SDL_RenderPresent(_renderer); //clear renderer
}
