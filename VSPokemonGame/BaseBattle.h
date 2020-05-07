#pragma once
#include "PokemonGen.h"
#include "BattleWindow.h"
#include "Player.h"

class BaseBattle
{
public:
	BaseBattle(Player* player, PokemonGen* pokemon2); //ctor, taking the player the pokemon to be battled
	virtual void InitilizeBattleWindow(); //function to open the battle window
	void BattleLoop(); //Main Battle loop
	virtual ~BaseBattle();
protected:
	BattleWindow* _battleWindow; //battle window object to display the progress and accept input
	Player* _player; //the player
	PokemonGen* _activePokemon1; //the players active pokemon
	PokemonGen* _activePokemon2; //the opposing pokemon
	bool _battleEnd; //boolean to track the end of the battle
	bool _turnEnd; //boolean to track if a turn has ended
	
	void BattleMenu(); //display the main battle menu
	void AttackSequence(); //select moves and determine which pokemon will attack first, 
	void SwitchPokemon(); //pokemon switching menu
	void UseItem(); //Bag menu
	virtual void Run(); //Escape from battle


public:
	const bool& Captured() const;
protected:
	void PokemonAttack(PokemonGen* attacker, PokemonGen* target, const int selected_move_index); //Use the selected move, by the attacker on the target
	void PokemonFainted(PokemonGen* other, PokemonGen* fainted); //Actions to take if a Poemon has fainted
	
	virtual bool CheckBattleEnd(); //check if the battle has ended
	bool CheckOwn(); //check if all of the player's pokemon have fainted
	virtual int OpponentSelectMove(); //function to select the opponents move
private:
	bool _captured; //if the pokemon has been caught
};

