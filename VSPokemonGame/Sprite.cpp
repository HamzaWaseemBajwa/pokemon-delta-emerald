#include "Sprite.h"
#include <SDL_image.h>
#include <iostream>


Sprite::Sprite(SDL_Renderer* passed_renderer, std::string file_path, const int x, const int y, const int w, const int h, double* p_camera_x, double* p_camera_y, CollisionRectangle* p_col_rect) :
	_renderer(passed_renderer),
	_cameraX(p_camera_x),
	_cameraY(p_camera_y),
	_collisionRectangle(p_col_rect),
	_rect({x, y, w, h})
{
	_image = IMG_LoadTexture(_renderer, file_path.c_str());

	if (_image == nullptr)
	{
		std::cout << "Could not load image " << file_path << '\n';
	}

	SDL_QueryTexture(_image, nullptr, nullptr, &_imageWidth, &_imageHeight);

	_camera.w = _rect.w;
	_camera.h = _rect.h;

	_crop.x = 0;
	_crop.y = 0;
	_crop.w = _imageWidth;
	_crop.h = _imageHeight;
}

Sprite::~Sprite()
{
	delete _collisionRectangle;
	SDL_DestroyTexture(_image);
}

void Sprite::Draw() 
{
	//set the image deistination w.r.t. current camera position

	_camera.x = _rect.x + static_cast<int>(*_cameraX);
	_camera.y = _rect.y + static_cast<int>(*_cameraY);

	SDL_RenderCopy(_renderer, _image, &_crop, &_camera); //draw image 


	if (_collisionRectangle != nullptr) //adjust collision rectangle w.r.t. Camera position
	{
		_collisionRectangle->SetX(_rect.x + static_cast<int>(*_cameraX));
		_collisionRectangle->SetY(_rect.y + static_cast<int>(*_cameraY));
		/*SDL_Rect rect = GetCollisionRectangle()->GetRectangle();
		SDL_RenderFillRect(_renderer, &rect);*/
	}
}

CollisionRectangle* Sprite::GetCollisionRectangle() const
{
	return _collisionRectangle;
}

void Sprite::DrawSteady() const
{
	SDL_RenderCopy(_renderer, _image, &_crop, &_rect);
	/*if (this->GetCollisionRectangle() != nullptr)
	{
		SDL_Rect rect = this->GetCollisionRectangle()->GetRectangle();
		SDL_RenderFillRect(_renderer, &rect);
	}*/
}


void Sprite::SetX(const int x) {
	_rect.x = x;
}

void Sprite::SetY(const int y) {
	_rect.y = y;
}

void Sprite::SetPosition(const int x, const int y) {
	_rect.x = x;
	_rect.y = y;
}

bool Sprite::RightCol(CollisionRectangle collider) const
{
	if (!(_collisionRectangle->GetRectangle().x + _collisionRectangle->GetRectangle().w < collider.GetRectangle().x))
	{
		if (_collisionRectangle->GetRectangle().x + _collisionRectangle->GetRectangle().w < collider.GetRectangle().x + collider.GetRectangle().w)
		{
			if (_collisionRectangle->GetRectangle().y < collider.GetRectangle().y + collider.GetRectangle().h)
			{
				if (_collisionRectangle->GetRectangle().y + _collisionRectangle->GetRectangle().h > collider.GetRectangle().y)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Sprite::BottomCol(CollisionRectangle collider) const
{
	if (!(_collisionRectangle->GetRectangle().y + _collisionRectangle->GetRectangle().h < collider.GetRectangle().y))
	{
		if (_collisionRectangle->GetRectangle().y < collider.GetRectangle().y)
		{
			if (_collisionRectangle->GetRectangle().x < collider.GetRectangle().x + collider.GetRectangle().w)
			{
				if (_collisionRectangle->GetRectangle().x + _collisionRectangle->GetRectangle().w > collider.GetRectangle().x)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Sprite::LeftCol(CollisionRectangle collider) const
{
	if (!(collider.GetRectangle().x + collider.GetRectangle().w < _collisionRectangle->GetRectangle().x))
	{
		if ((collider.GetRectangle().x + collider.GetRectangle().w < _collisionRectangle->GetRectangle().x + _collisionRectangle->GetRectangle().w))
		{
			if (_collisionRectangle->GetRectangle().y < collider.GetRectangle().y + collider.GetRectangle().h)
			{
				if (_collisionRectangle->GetRectangle().y + _collisionRectangle->GetRectangle().h > collider.GetRectangle().y)
				{
					return true;
				}
			}
		}

	}
	return false;
}

bool Sprite::TopCol(CollisionRectangle collider) const
{
	if (!(collider.GetRectangle().y + collider.GetRectangle().h < _collisionRectangle->GetRectangle().y))
	{
		if (collider.GetRectangle().y + collider.GetRectangle().h < _collisionRectangle->GetRectangle().y + _collisionRectangle->GetRectangle().h)
		{
			if (_collisionRectangle->GetRectangle().x < collider.GetRectangle().x + collider.GetRectangle().w)
			{
				if (_collisionRectangle->GetRectangle().x + _collisionRectangle->GetRectangle().w > collider.GetRectangle().x)
				{
					return true;
				}
			}
		}

	}
	return false;
}

int Sprite::GetImageWidth() const
{
	return _imageWidth;
}

int Sprite::GetImageHeight() const
{
	return _imageHeight;
}

SDL_Rect* Sprite::GetCrop()
{
	return &_crop;
}


int Sprite::GetX() const
{
	return _rect.x;
}

int Sprite::GetY() const
{
	return _rect.y;
}

int Sprite::GetW() const
{
	return _rect.w;
}

int Sprite::GetH() const
{
	return _rect.h;
}



