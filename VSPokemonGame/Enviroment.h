#pragma once
#include "Sprite.h"
#include "SdlSetup.h"
#include "Tree.h"
#include <vector>
#include <string>
#include "Building.h"
#include "Zone.h"
#include "Trainer.h"
#include "ItemPickup.h"

class Enviroment
{
public:
	Enviroment(SdlSetup* p_sdl_setup, int p_screen_width, int p_screen_height, double* p_camera_x, double* p_camera_y);

	void DrawBack(); //draw elements that go behind the player sprite
	void DrawFront();	//draw elemtns that come infront of the player sprite

	void LoadEnivroment(); //load the environments data from files
	void SaveEnviroment();	//save environment data to files

	std::vector<Sprite*> GetGrass() const;	//get the environments grass tiles
	std::vector<ItemPickup*>& GetItems();	//get the envionements free items

	Sprite* GetPokemonCenter();	//ge the postion of the pokemon center

	void PokemonActive();	//make the pokemon sprite active
	void UpdateZone();	//updates the curretn zone the player is in
	void Update();	//updates the envrionments animations
	void PlayAnimation(double speed);	//plays the envionments water animations
	void PlayPokemonAnimation();	//plays the environments pokemon animation
	std::vector<CollisionRectangle*> GetCollisionRects();	//returns the enivoronments collision rectangles
	std::vector<Trainer*> GetTrainers() const;	//returns the trainers in the environment

	Sprite* legendary_pokemon;	//Environment legendary pokemon


	std::string DisplayName() const;	//Returns the name of the current zone

	~Enviroment();

private:
	//SDL Setup, screen dimesnions and Camera position

	SdlSetup* _sdlSetup;

	double* _cameraX;
	double* _cameraY;

	int _screenWidth;
	int _screenHeight;

	//name of environment

	std::string _environmentName;
	std::string _displayName;

	//current zone 

	Zone* _noZone;
	Zone* _currentZone;

	//environment background dimensios

	int _dimensions[2];

	//environment object vectors

	std::vector<Sprite*> _background;
	std::vector<Tree*> _trees;
	std::vector<Building*> _buildings;
	std::vector<Sprite*> _waterTiles;
	std::vector<Sprite*> _grassTiles;
	std::vector<Sprite*> _borders;
	std::vector<Zone*> _zones;
	std::vector<Trainer*> _trainers;
	std::vector<ItemPickup*> _itemPickups;

	//enivronment animation variables 

	int _currentFrameWater;
	int _currentFramePokemon;

	bool _reflect;
	int _maxLimit;

	int _row;
	int _speed;

	int _animationDelay;
	int _animationDelayB;
};

