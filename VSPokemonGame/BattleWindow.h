#pragma once
#include "SdlSetup.h"
#include "PokemonGen.h"
#include "PokemonSprite.h"
#include "Button.h"
#include <vector>
#include "Trainer.h"
#include "Player.h"

class BattleWindow
{
public:
	BattleWindow(Player* player, PokemonGen* pokemon1, PokemonGen* pokemon2); //constructor for base battle
	void AttackAnimation(PokemonGen* attacker) const;
	BattleWindow(Player* player, PokemonGen* pokemon1, Trainer* trainer); //constructor for trainer battle
	void BattleStartMessage(); //message and animation shown at start of battle
	void SetDefaultBackground();	//set the default empty menu background
	void DisplayBattleMenu(int& choice);	//Display the battle menu and store the value into the passed parameter
	void ClearMenu(); //clear the menu and buttons
	void DisplayAttackMenu(int& choice); //Display the attack menu and pass the value into the passed parameter
	void DisplayPokemonSet(int& choice); //Display the pokemon selection menu and pass the value into the passed parameter
	void DisplayBag(int& choice); //Display the bag menu and pass the value into the passed parameter
	void UpdateStatus(PokemonGen* pokemon1, PokemonGen* pokemon2); //Update pokemon status bars
	void operator<<(const std::string text);	//overloaded operator for displaying text on the battle screen
	void FaintingAnimation(PokemonGen* pokemon) const; //Animation to play when a pokemon has fainted
	void BattleStart() const;
	void Update(PokemonGen* pokemon1, PokemonGen* pokemon2);

	~BattleWindow();

private:
	Player* _player;
	PokemonGen* _pokemon1;
	PokemonGen* _pokemon2;
	Trainer* _opponent;
	PokemonSprite* _ownPokemonSprite;
	PokemonSprite* _oppPokemonSprite;
	bool _battleQuit;
	SdlSetup* _battleSdlSetup;
	std::string _battleText;
	Sprite* _battleBackground;
	void BattleStatusBar(int x, int y, int w, int h, PokemonGen* pokemon, int passed_hp) const;
	void UpdateText(std::string text);
	void RenderText() const;
	int _pokemon1LastHp;
	int _pokemon2LastHp;
	Sprite* _menuBackground;
	std::vector<Button*> _buttons;
};

