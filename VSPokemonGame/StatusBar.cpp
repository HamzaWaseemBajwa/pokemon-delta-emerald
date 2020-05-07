#include "StatusBar.h"
#include "MainClass.h"
#include <string>
#include <ctime>
#include <chrono>

StatusBar::StatusBar(SdlSetup* sdl_setup)
{
	_background = { 0,0, 720, 40 };
	_sdlSetup = sdl_setup;

	_locationName = new Text(_sdlSetup, 200, 0, 20);
	_currentTime = new Text(_sdlSetup, 450, 0, 20);
	_trainerMoney = new Text(_sdlSetup, 550, 0, 20);

	int offX = 5;
	for (int i = 0; i < 6; ++i)	//load the icon sprites, with offesets for each slot
	{	
		_statusIcons[i][0] = new Sprite(_sdlSetup->GetRenderer(), "Resources/pokeball_none.png", 5 + offX, 5, 32, 32, nullptr, nullptr, nullptr);
		_statusIcons[i][1] = new Sprite(_sdlSetup->GetRenderer(), "Resources/pokeball_healthy.png", 5 + offX, 5, 32, 32, nullptr, nullptr, nullptr);
		_statusIcons[i][2] = new Sprite(_sdlSetup->GetRenderer(), "Resources/pokeball_fainted.png", 5 + offX, 5, 32, 32, nullptr, nullptr, nullptr);
		_statusIcons[i][3] = new Sprite(_sdlSetup->GetRenderer(), "Resources/pokeball_status.png", 5 + offX, 5, 32, 32, nullptr, nullptr, nullptr);
		offX += 32;
	}
}

StatusBar::~StatusBar()
{
	//clear the icons and text
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			delete _statusIcons[i][j];
		}
	}
	delete _trainerMoney;
	delete _locationName;
	delete _currentTime;
}

void StatusBar::Draw(Player* player, Enviroment* current) const
{	
	//draw the background rect
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 255, 255, 255, 0);
	SDL_RenderFillRect(_sdlSetup->GetRenderer(), &_background);
	SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), 0, 0, 0, 0);
	struct tm newtime;
	time_t now = time(nullptr);
	localtime_s(&newtime, &now);

	//draw the text

	_currentTime->Update(std::to_string(newtime.tm_hour) + ':' + (newtime.tm_min / 10.0 >= 1 ? "" : "0") + std::to_string(newtime.tm_min));
	_trainerMoney->Update("$ " + std::to_string(player->GetMoney()) + +".00");
	_locationName->Update(current->DisplayName());

	//draw the pokemon icons, reflecting the pokemon's status

	for (int i = 0; i < 6; ++i)
	{
		if (player->PokemonSet()[i] == nullptr)
		{
			_statusIcons[i][0]->DrawSteady();
		}
		else
		{
			switch (player->PokemonSet()[i]->Status())
			{
			case NoEffect:
				_statusIcons[i][1]->DrawSteady();
				break;
			case Faint:
				_statusIcons[i][2]->DrawSteady();
				break;
			default:
				_statusIcons[i][3]->DrawSteady();
				break;
			}
		}
	}
}
