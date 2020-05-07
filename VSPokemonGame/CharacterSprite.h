#pragma once
#include "Sprite.h"
#include "SdlSetup.h"

class CharacterSprite
{
public:
	CharacterSprite(SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, int x, int y, std::string file_name);

	void DrawChar() const;	//draw the sprite
	Sprite* GetImage() const; //get the image (for collision detection etc.)

	virtual ~CharacterSprite();

protected:
	Sprite* _characterImage; //characters images sprite
	double* _cameraX; //camera coordinates for drawing in the environment
	double* _cameraY;
	SdlSetup* _sdlSetup;	//SDL setup where the sprite must be drawn
};