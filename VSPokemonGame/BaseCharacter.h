#pragma once
#include <string>
#include "CharacterSprite.h"

class BaseCharacter //classto display non-battling characters in the overworld
{
public:
	BaseCharacter(const std::string character_class, const std::string name, SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, const int x, const int y);
	
	//getters

	CharacterSprite* GetSprite() const;
	std::string GetName() const;
	std::string GetClass() const;

	virtual ~BaseCharacter();
protected:
	CharacterSprite* _characterImage; //charactrs image sprite
	std::string _name; //characters name
	std::string _characterClass; //character class (Trainer, Hiker, Doctor etc..)
};

