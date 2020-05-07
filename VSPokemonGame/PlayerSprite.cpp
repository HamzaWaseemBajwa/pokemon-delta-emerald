#include "PlayerSprite.h"
#include "Sound.h"

PlayerSprite::PlayerSprite(SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, const std::string file_name, Enviroment* passed_environment) : CharacterSprite(passed_sdl_setup, p_camera_x, p_camera_y, 296, 296, file_name)
{
	delete _characterImage; //delete the sprite created in the base contructor
	_characterImage = new Sprite(_sdlSetup->GetRenderer(), "Resources/CharacterSprites/" + file_name, 328, 328, 64, 64, p_camera_x, p_camera_y, new CollisionRectangle(336, 336, 48, 48));
	_enviroment = passed_environment;
	SetUpAnimation(4, 4);
	_up = false;
	_down = false;
	_left = false;
	_right = false;
}

PlayerSprite::~PlayerSprite()
{
}

void PlayerSprite::PlayAnimation(const int begin_frame, const int end_frame, const int row, const double speed)
{
	if (_animationDelay + speed < SDL_GetTicks() || _currentFrame == -1) //if the set amount of time ha passed since the last update
	{
		if (_currentFrame == end_frame) // if the current frame is last frame in the row, set the frame to the initial frame
		{
			_currentFrame = begin_frame - 1;
		}
		else
		{
			++_currentFrame;	//increment the frame
			_characterImage->GetCrop()->x = _currentFrame * (_characterImage->GetImageWidth() / _amountFrameX); //set the crop location accoriding to the frame and direction movement
			_characterImage->GetCrop()->y = row * (_characterImage->GetImageHeight() / _amountFrameY);
			_characterImage->GetCrop()->w = _characterImage->GetImageWidth() / _amountFrameX; //set the crop to the correct size
			_characterImage->GetCrop()->h = _characterImage->GetImageHeight() / _amountFrameY;
		}
		_animationDelay = SDL_GetTicks();
	}
}


//movement functions, when called, play the appropirate animation for the direction of movement
//adjust camera position for the movement, until the player collides with an object
//move 5 units for each press

void PlayerSprite::MoveUp()
{
	PlayAnimation(0, 3, 3, 200);	
	if (!CharacterColTop())
	{
		for (int i = 0; i < 5; i++)
		{
			(*_cameraY)++;
			if (CharacterColTop())
			{
				(*_cameraY)--;
			}
		}
	}
	else
	{
		Sound::PlaySound("Collision");
	}
}



void PlayerSprite::MoveDown()
{
	PlayAnimation(0, 3, 0, 200);
	if (!CharacterColBottom())
	{
		for (int i = 0; i < 5; i++)
		{
			(*_cameraY)--;
			if (CharacterColBottom())
			{
				(*_cameraY)++;

			}
		}
	}
	else
	{
		Sound::PlaySound("Collision");
	}
}

void PlayerSprite::MoveLeft()
{
	PlayAnimation(0, 3, 1, 200);
	if (!CharacterColLeft())
	{
		for (int i = 0; i < 5; i++)
		{
			(*_cameraX)++;
			if (CharacterColLeft())
			{
				(*_cameraX)--;
			}
		}
	}
	else
	{
		Sound::PlaySound("Collision");
	}
}



void PlayerSprite::MoveRight()
{
	PlayAnimation(0, 3, 2, 200);
	if (!CharacterColRight())
	{
		for (int i = 0; i < 5; i++)
		{
			(*_cameraX)--;
			if (CharacterColRight())
			{
				(*_cameraX)++;
			}
		}
	}
	else
	{
		Sound::PlaySound("Collision");
	}
}

void PlayerSprite::Draw() const
{
	_characterImage->DrawSteady();
}

//collison functions
//get the collisons rects from the environment
//loop for each collision rect and check if the player collides with it in the desired direction

bool PlayerSprite::CharacterColLeft() const
{
	for (auto element : _enviroment->GetCollisionRects())
	{
		if (_characterImage->LeftCol(*element))
		{
			return true;
		}
	}
	return false;
}

bool PlayerSprite::CharacterColRight() const
{
	for (auto element : _enviroment->GetCollisionRects())
	{
		if (_characterImage->RightCol(*element))
		{
			return true;
		}
	}
	return false;
}

bool PlayerSprite::CharacterColTop() const
{
	for (auto element : _enviroment->GetCollisionRects())
	{
		if (_characterImage->TopCol(*element))
		{
			return true;
		}
	}
	return false;
}

bool PlayerSprite::CharacterColBottom() const
{
	for (auto element : _enviroment->GetCollisionRects())
	{
		if (_characterImage->BottomCol(*element))
		{
			return true;
		}
	}
	return false;
}

void PlayerSprite::SetUpAnimation(const int passed_amount_frame_x, const int passed_amount_frame_y) 
{
	_amountFrameX = passed_amount_frame_x;
	_amountFrameY = passed_amount_frame_y;
	_characterImage->GetCrop()->x = 0;
	_characterImage->GetCrop()->y = 0;
	_characterImage->GetCrop()->w = _characterImage->GetImageWidth() / _amountFrameX;
	_characterImage->GetCrop()->h = _characterImage->GetImageHeight() / _amountFrameY;
}

void PlayerSprite::Update()	
{
	//for each key press, call the appropirate movement function, once per frame
	switch (_sdlSetup->GetMainEvent()->type)
	{
	case SDL_KEYDOWN:
		switch (_sdlSetup->GetMainEvent()->key.keysym.sym)
		{
		case SDLK_a:
			_left = true;
			break;
		case SDLK_s:
			_down = true;
			break;
		case SDLK_d:
			_right = true;
			break;
		case SDLK_w:
			_up = true;
			break;
		default:
			break;
		}
	case SDL_KEYUP:
		switch (_sdlSetup->GetMainEvent()->key.keysym.sym)
		{
		case SDLK_a:
			if (_left)
			{
				MoveLeft();
				_left = false;
			}
			break;
		case SDLK_s:
			if (_down)
			{
				MoveDown();
				_down = false;
			}
		case SDLK_d:
			if (_right)
			{
				MoveRight();
				_right = false;
			}
			break;
		case SDLK_w:
			if (_up)
			{
				MoveUp();
				_up = false;
			}
			break;
		default:
			break;
		}
	default:
		break;
	}
}


