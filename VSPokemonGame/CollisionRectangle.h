#pragma once
#include <SDL.h>

class CollisionRectangle
{
public:
	CollisionRectangle(int x, int y, int w, int h);
	void SetRectangle(int x, int y, int w, int h);
	SDL_Rect GetRectangle() const;
	void SetX(const int x);
	void SetY(const int y);

	~CollisionRectangle();
private:
	int _offsetX;	//the horizontal offeset of the collison rectangle wrt to the sprite
	int _offsetY; //the vetrical offeset of the collison rectangle wrt to the sprite
	SDL_Rect _collisionRect;	//dimensions of the collision rectangle
};

