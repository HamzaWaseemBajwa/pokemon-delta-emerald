#pragma once
#include "SdlSetup.h"
#include "Sprite.h"
#include "Text.h"
#include <array>
#include "Player.h"

class StatusBar
{
public:
	explicit StatusBar(SdlSetup* sdl_setup);
	~StatusBar();
	void Draw(Player* player, Enviroment* current) const;
private:
	SdlSetup* _sdlSetup;	//setup where the bar is drawn
	Text* _currentTime;		//text for the current time
	Text* _locationName;	//text for the current enviroment zone name
	Text* _trainerMoney;	//text for the trainers money
	std::array<std::array<Sprite*, 4>, 6> _statusIcons;	//nested array of icons to represent the players pokemon and their status
	SDL_Rect _background;	//background rect
};

