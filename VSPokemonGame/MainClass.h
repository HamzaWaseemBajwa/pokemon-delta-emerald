#pragma once
#include "SdlSetup.h"
#include "Enviroment.h"
#include "Player.h"
#include "StatusBar.h"

class MainClass
{
public:
	enum DisplayMode //Display mode enum for Pokemon Display function
	{
		SwitchPokemon,
		UseItem
	};

	MainClass(); //ctor
	
	void TitleScreen() const; //Display the Title screen animation 
	void StartScreen() const; //Display the save file selection screen
	void GameLoop(); //main game loop
	

	~MainClass();

private:
	void DisplayBag() const; //Display the player's bag
	void RandomWildBattle() const;
	void PlayerMoved() const; //Actions to take if player has moved
	void PlayerInteract() const; //Actions to take if player interacts with an object
	void PokemonStatusBar(int x, int y, int w, int h, PokemonGen* pokemon) const; //Pokemon status bar, for use in the Pokemon display function
	void DisplayPokemonSet(DisplayMode mode, Item* item) const; //Display the player's pokemon set, if display mode is item, also pass the item to be used
	void Update(); //Manages key presses
	void LoadSaveFile(); //Load the player data from the save file
	void CheckPokemonFainted(); //actions to take if all of the player's Pokemom have fainted
	void SaveFile() const; //Save the players datato the save file

	double _cameraX; //current camera X coordinate
	double _cameraY; //current camera Y coordinate

	int _screenWidth; 
	int _screenHeight;

	bool _quit; //quit variable to end game

	SdlSetup* _sdlSetup; //SDL Setup for game display

	StatusBar* _statusBar; //information bar 
	Player* _player; //main player object
	Enviroment* _current; //current 

	//booleans to ensure only on key press is registered per frame

	bool _fileSaved; 
	bool _showBag;
	bool _showPokemon;
	bool _helpMenu;
	bool _interact;
};

