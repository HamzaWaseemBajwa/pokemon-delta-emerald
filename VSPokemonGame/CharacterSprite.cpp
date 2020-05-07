#include "CharacterSprite.h"
#include "MainClass.h"
#include <SDL.h>
#include <fstream>

CharacterSprite::CharacterSprite(SdlSetup* passed_sdl_setup, double* p_CameraX, double* p_CameraY, int x, int y, const std::string file_name)
{
	_cameraX = p_CameraX;
	_cameraY = p_CameraY;
	_sdlSetup = passed_sdl_setup;
	_characterImage = new Sprite(_sdlSetup->GetRenderer(), "Resources/CharacterSprites/Overworld/" + file_name + ".png", x, y, 64, 64, _cameraX, _cameraY, new CollisionRectangle(10, 16, 32, 40));
}


CharacterSprite::~CharacterSprite()
{
	delete _characterImage;
}

void CharacterSprite::DrawChar() const
{
	_characterImage->Draw();
}

Sprite* CharacterSprite::GetImage() const
{
	return _characterImage;
}

