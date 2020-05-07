#include "PokemonSprite.h"

PokemonSprite::PokemonSprite(SdlSetup* passed_setup)
{
	_sdlSetup = passed_setup;
	_front = nullptr;
	_back = nullptr;
	_icon = nullptr;
	_pokemonNo = "";
}

void PokemonSprite::Update(const std::string pokemon_no, const int x, const int y)
{
	if (_pokemonNo != pokemon_no) //if stored pokemon has been changed, delete previous sprites and load new sprites
	{
		delete _front;
		delete _back;
		delete _icon;
		_front = new Sprite(_sdlSetup->GetRenderer(), "Resources/PokemonSprites/front/" + pokemon_no + ".png", x, y, 128, 128,
			nullptr, nullptr, nullptr);
		_back = new Sprite(_sdlSetup->GetRenderer(), "Resources/PokemonSprites/back/" + pokemon_no + ".png", x, y, 128, 128,
			nullptr, nullptr, nullptr);
		_icon = new Sprite(_sdlSetup->GetRenderer(), "Resources/PokemonSprites/icon/" + pokemon_no + ".png", x, y, 128, 128,
			nullptr, nullptr, nullptr);
	}
	_pokemonNo = pokemon_no;
	_front->SetPosition(x, y);
	_back->SetPosition(x, y);
	_icon->SetPosition(x, y);
}

void PokemonSprite::DrawFront() const
{
	_front->DrawSteady();
}

void PokemonSprite::DrawBack() const
{
	_back->DrawSteady();
}

void PokemonSprite::DrawIcon() const
{
	_icon->DrawSteady();
}

PokemonSprite::~PokemonSprite()
{
	delete _front;
	delete _back;
	delete _icon;
}

