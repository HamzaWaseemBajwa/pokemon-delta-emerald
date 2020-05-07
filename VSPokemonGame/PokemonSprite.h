#pragma once
#include "Sprite.h"
#include "SdlSetup.h"

class PokemonSprite
{
public:
	explicit PokemonSprite(SdlSetup* passed_setup); //ctor

	void Update(const std::string pokemon_no, int x, int y); //update the sprite location and pokemon

	void DrawFront() const; 
	void DrawBack() const;
	void DrawIcon() const;

	~PokemonSprite();
private:
	SdlSetup* _sdlSetup; //setup where the sprite is displayed
	std::string _pokemonNo; //index no of displayed pokemon
	Sprite* _front; //front view sprite
	Sprite* _back; //rear view sprite
	Sprite* _icon; //icon sprite
};