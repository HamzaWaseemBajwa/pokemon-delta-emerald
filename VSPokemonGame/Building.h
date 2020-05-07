#pragma once
#include "SdlSetup.h"
#include "Sprite.h"
class Building
{
public:
	Building(SdlSetup* sdl_setup, std::string name, double* camera_x, double* camera_y, int x, int y, int w, int front_h);
	~Building();
	
	//draw the different parts of the building
	void DrawFront() const;
	void DrawBack() const;

	//getters

	Sprite* const& GetFront() const;
	std::string GetName() const;
private:
	std::string _name;
	Sprite* _image;
};