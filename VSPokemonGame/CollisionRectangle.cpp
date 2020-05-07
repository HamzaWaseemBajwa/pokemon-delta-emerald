#include "CollisionRectangle.h"



CollisionRectangle::CollisionRectangle(const int x, const int y, const int w, const int h)
{
	_offsetX = x;
	_offsetY = y;
	SetRectangle(0, 0, w, h);
}

CollisionRectangle::~CollisionRectangle()
{
}

void CollisionRectangle::SetRectangle(const int x, const int y, const int w, const int h)
{
	_collisionRect.x = x + _offsetX;
	_collisionRect.y = y + _offsetY;
	_collisionRect.w = w;
	_collisionRect.h = h;
}

SDL_Rect CollisionRectangle::GetRectangle() const
{
	return _collisionRect;
}

void CollisionRectangle::SetX(const int x)
{
	_collisionRect.x = _offsetX + x;
}

void CollisionRectangle::SetY(const int y)
{
	_collisionRect.y = _offsetY + y;
}

