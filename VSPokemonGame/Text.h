#pragma once
#include "SdlSetup.h"
#include "Sprite.h"
#include <vector>
#include <array>

class Text
{
public:
	Text(SdlSetup* passed_setup, int x, int y, int size); //ctor, taking text location and font size
	void Update(std::string); //draw the passed string 
	~Text();
private:
	SdlSetup* _sdlSetup; //setup where the text is drawn
	std::string _text; 
	int _x;
	int _y;
	double _fontSize;
	Sprite* _font; //font image
	std::vector<std::array<int, 2>> _characters; //vector of charactr position coordinates
};

