#include "Building.h"

Building::Building(SdlSetup* sdl_setup, const std::string name, double* camera_x, double* camera_y, const int x, const int y, const int w, const int front_h)
{
	_name = name;
	_image = new Sprite(sdl_setup->GetRenderer(), "Resources/Environment/Buildings/" + name + ".png", x, y, w, front_h, camera_x, camera_y, new CollisionRectangle(10, 30, w - 10, front_h - 40));
}

Building::~Building()
{
	delete _image;
}

void Building::DrawBack() const
{
	_image->Draw();
}

Sprite* const& Building::GetFront() const
{
	return _image;
}

std::string Building::GetName() const
{
	return _name;
}

void Building::DrawFront() const
{
	_image->Draw();
}
