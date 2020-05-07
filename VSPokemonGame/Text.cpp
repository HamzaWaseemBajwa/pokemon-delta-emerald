#include "Text.h"
#include "SdlSetup.h"
#include "Sprite.h"
#include <string>
#include <cctype>

Text::Text(SdlSetup* passed_setup, int x, int y, const int size)
{
	_x = x;
	_y = y;
	_sdlSetup = passed_setup;
	_text = "";
	_fontSize = size / 10;
	_font = new Sprite(_sdlSetup->GetRenderer(), "Resources/font.png", _x, _y, 16 * static_cast<int>(_fontSize), 25 * static_cast<int>(_fontSize), nullptr, nullptr, nullptr);
}

void Text::Update(const std::string text)
{
	if (text != _text) //if text has changed
	{
		_characters.clear(); //clear the char position array
		for (char c : text)//loop for each character in string
		{
			int offX = -1; //reset offsets
			int offY = -1;
			if (c != ' ') 
			{
				if (std::isdigit(c)) 
				{
					//set offsetX with respect to distance from 0
					offX = int(c) - int('0');
					offY = 2;
				}
				else if (std::isalpha(c))
				{
					//set offsetX with respect to distance from a
					offX = int(std::toupper(c)) - int('A');
					//set offsetY wrt character case
					offY = c == toupper(c) ? 0 : 1;
				}
				else
				{
					//handle special characters
					switch (c)
					{
					case ':':
						offX = 2;
						break;
					case '!':
						offX = 4;
						break;
					case '$':
						offX = 15;
						break;
					case '?':
						offX = 5;
						break;
					case '.':
						offX = 1;
						break;
					case '/':
						offX = 20;
					default:
						break;
					}
					offY = 3;
				}
			}
			//add X, Y offsets to vector
			_characters.push_back({ offX, offY });
		}
	}

	//set stroed text to passed text
	_text = text;

	//drawing sequence
	int xPos = 0; //initlal x
	for (std::array<int,2> character : _characters)
	{
		if (character[0] != -1 && character[1] != -1) //if not a space ' ' 
		{
			_font->SetX(_x + static_cast<int>(_fontSize) * xPos * 8); //set the character X location
			_font->GetCrop()->x = (_font->GetImageWidth() / 26) * character[0]; //get the correct crop
			_font->GetCrop()->y = (_font->GetImageHeight() / 4) * character[1];
			_font->GetCrop()->w = (_font->GetImageWidth() / 26);
			_font->GetCrop()->h = (_font->GetImageHeight() / 4);
			_font->DrawSteady(); //draw crop
		}
		++xPos;
	}
}

Text::~Text()
{
	delete _font;
}
