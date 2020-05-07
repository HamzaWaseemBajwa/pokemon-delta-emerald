#include "Zone.h"

Zone::Zone(SdlSetup* passed_setup, int x, int y, int w, int h, double* camera_x, double* camera_y, const std::string name)
{
	_sdlSetup = passed_setup;
	_name = name;
	_zoneSprite = new Sprite(_sdlSetup->GetRenderer(), "Resources/colRect.png", x, y, w, h, camera_x, camera_y, nullptr);
}

Zone::~Zone()
{
	delete _zoneSprite;
}

std::string& Zone::Name()
{
	return _name;
}

Sprite*& Zone::ZoneSprite()
{
	return _zoneSprite;
}
