#pragma once
#include <string>
#include "SdlSetup.h"
#include "Sprite.h"

class Sprite;

class Zone
{
public:
	Zone(SdlSetup* passed_setup, int x, int y, int w, int h, double* camera_x, double* camera_y, std::string name);
	
	std::string& Name();
	Sprite*& ZoneSprite();

	~Zone();
private:
	SdlSetup* _sdlSetup;
	std::string _name;
	Sprite* _zoneSprite;
};

