#include "Button.h"
#include "Text.h"

Button::Button(SdlSetup* passed_setup, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b)
{
	_sdlSetup = passed_setup;
	_buttonRect = {x, y, w, h};
	_color = {r, g, b};
}

Button::Button(SdlSetup* passed_setup, int x, int y, int w, int h)
{
	_sdlSetup = passed_setup;
	_buttonRect = {x, y, w, h};
	_color = {255,255,255,0};
}

void Button::Draw() const //draw button, only if not black, used only for testing
{
	if (!(_color.r == 0 && _color.g == 0 && _color.b == 0))
	{
		SDL_Color old;
		SDL_GetRenderDrawColor(_sdlSetup->GetRenderer(), &old.r, &old.g, &old.b, &old.a);
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), _color.r, _color.g, _color.b, _color.a);
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &_buttonRect);
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), old.r, old.g, old.b, old.a);
		SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &_buttonRect);
	}
}

void Button::Draw(PokemonMove* passed_move, const int pp)
{
	switch (passed_move->MoveType()) //set button color depending on move type
	{
	case Normal:
		_color = {235,235,235,0};
		break;
	case Fire:
		_color = {255,150,0,0};
		break;
	case Water:
		_color = {0,165,255,0};
		break;
	case Electric:
		_color = {255,235,0,0};
		break;
	case Grass:
		_color = {0,200,0,0};
		break;
	case Ice:
		_color = {255,225,105,0};
		break;
	case Fighting:
		_color = {180,0,0,0};
		break;
	case Poison:
		_color = {165,0,255,0};
		break;
	case Ground:
		_color = {220, 180, 90,0};
		break;
	case Flying:
		_color = {200, 200,255,0};
		break;
	case Psychic:
		_color = {190, 65,255,0};
		break;
	case Bug:
		_color = {165, 165,0,0};
		break;
	case Rock:
		_color = {165, 135,0,0};
		break;
	case Ghost:
		_color = {120,120, 165,0};
		break;
	case Dragon:
		_color = {110,0,255,0};
		break;
	case Dark:
		_color = {40, 40,40,0};
		break;
	case Steel:
		_color = {165, 165,165,0};
		break;
	case None: break;
	default: ;
	}
	if (!(_color.r == 0 && _color.g == 0 && _color.b == 0))
	{
		SDL_Color old; //get previous renderer color
		SDL_GetRenderDrawColor(_sdlSetup->GetRenderer(), &old.r, &old.g, &old.b, &old.a);
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), _color.r, _color.g, _color.b, _color.a);
		SDL_RenderFillRect(_sdlSetup->GetRenderer(), &_buttonRect);
		Text text1{_sdlSetup, _buttonRect.x, _buttonRect.y, 10}; //display move information as text
		text1.Update(passed_move->Name());
		Text text2{_sdlSetup, _buttonRect.x, _buttonRect.y + 20, 10};
		text2.Update(std::to_string(pp) + '/' + std::to_string(passed_move->BasePp()));
		SDL_SetRenderDrawColor(_sdlSetup->GetRenderer(), old.r, old.g, old.b, old.a); //revert to old color
		SDL_RenderDrawRect(_sdlSetup->GetRenderer(), &_buttonRect); //draw outline
	}
}

void Button::ClickedAnimation() const
{
	SDL_RenderFillRect(_sdlSetup->GetRenderer(), &_buttonRect); //set color as rendereror color
}

bool Button::Clicked(const int x, const int y) const //if passed x and y cooordinates are inside the button, return true
{
	if (x > _buttonRect.x && x < _buttonRect.x + _buttonRect.w)
	{
		if (y > _buttonRect.y && y < _buttonRect.y + _buttonRect.h)
		{
			return true;
		}
	}
	return false;
}

Button::~Button()
{
}
