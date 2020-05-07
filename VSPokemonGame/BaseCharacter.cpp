#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(const std::string character_class, const std::string name, SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y,
                             const int x, const int y):
 	_characterImage(new CharacterSprite(passed_sdl_setup, p_camera_x, p_camera_y, x, y, character_class + name)),
	_name(name),
	_characterClass(character_class)
{
}

CharacterSprite* BaseCharacter::GetSprite() const
{
	return _characterImage;
}

BaseCharacter::~BaseCharacter()
{
	delete _characterImage;
}

std::string BaseCharacter::GetName() const
{
	return _name;
}

std::string BaseCharacter::GetClass() const
{
	return _characterClass;
}
