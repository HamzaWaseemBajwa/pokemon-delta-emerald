#pragma once
#include "CharacterSprite.h"
#include "Enviroment.h"

class PlayerSprite : public CharacterSprite //derives from Charcter sprite, adding the neccassary functionality for collisions, movement and animation
{
public:
	PlayerSprite(SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, std::string file_name, Enviroment* passed_environment);
	
	void Update(); //function to update the players sprite to relect movement
	void Draw() const; //draw the player's sprite

	~PlayerSprite();

private:
	Enviroment* _enviroment; //environment in which the player is situated
	int _amountFrameX;	//frames in the players character sprite sheet
	int _amountFrameY;

	int _timeCheck;	//time check to update the player's sprite after a certain delay
	int _animationDelay; //the delay after which the time must be updated

	int _currentFrame;	//the current horizontal frame of the sprite sheet
	
	//variables to track the players direction of movement

	bool _up;
	bool _down;
	bool _left;
	bool _right;
	
	//functions to return the direction of collision 

	bool CharacterColLeft() const;
	bool CharacterColRight() const;
	bool CharacterColTop() const;
	bool CharacterColBottom() const; 

	void PlayAnimation(int begin_frame, int end_frame, int row, double speed);	//display the correct frame of movement, according to the passed direction
	void SetUpAnimation(int passed_amount_frame_x, int passed_amount_frame_y);	//adjust the sprite sheet's crop size to the passed amount of frames

	//functions to handle the player's movement amount and direction

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};

