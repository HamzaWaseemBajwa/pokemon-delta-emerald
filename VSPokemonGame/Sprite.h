#pragma once
#include "CollisionRectangle.h"
#include <string>
#include <SDL.h>

class Sprite //Class for handling all images within the gae
{
public:
	Sprite(SDL_Renderer* passed_renderer, std::string file_path, int x, int y, int w, int h, double* p_camera_x, double* p_camera_y, CollisionRectangle* p_col_rect);

	void Draw(); //draw the image with respect to the camera location

	CollisionRectangle* GetCollisionRectangle() const; //get the sprite's collision rectangle

	void DrawSteady() const; //draw the image without respect to the camera location

	void SetX(int x); //set the images X coordinate

	void SetY(int y); //set the images X coordinate

	//dimesnion and coordinate getters

	int GetX() const;
	int GetY() const;
	int GetW() const;
	int GetH() const;


	void SetPosition(int x, int y);

	//collision handlers

	bool LeftCol(CollisionRectangle collider) const;
	bool BottomCol(CollisionRectangle collider) const;
	bool RightCol(CollisionRectangle collider) const;
	bool TopCol(CollisionRectangle collider) const;

	//Get actual width

	int GetImageWidth() const;
	int GetImageHeight() const;

	//Get current crop

	SDL_Rect* GetCrop();

	~Sprite();
private:

	SDL_Texture* _image; //load image
	SDL_Rect _rect; //image rectangle
	SDL_Rect _crop; //image crop rectangle
	SDL_Rect _camera; //image rectqangle w.r.t. Camera position

	SDL_Renderer* _renderer;

	double* _cameraX;
	double* _cameraY;

	int _imageWidth;
	int _imageHeight;

	CollisionRectangle* _collisionRectangle;
};

