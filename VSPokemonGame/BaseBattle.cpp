#include "BaseBattle.h"
#include <ctime>
#include <iostream>
#include "Player.h"
#include "Sound.h"

BaseBattle::BaseBattle(Player* player, PokemonGen* pokemon2) : _turnEnd(false)
{
	_player = player;
	_activePokemon1 = nullptr;
	int i = 0;
	for (PokemonGen* pokemon : _player->PokemonSet()) //select the first non fainted pokemon, and set as active 
	{
		if (pokemon->Status() != Faint)
		{
			_activePokemon1 = pokemon;
			if (i != 0) //if the pokemon is not the frist pokemon in the set
			{
				//replace the active pokemon with the firt pokemon
				PokemonGen* temp = _player->PokemonSet()[0];
				_player->PokemonSet()[0] = pokemon;
				_player->PokemonSet()[i] = temp;
			}
			break;
		}
		++i;
	}
	_activePokemon2 = pokemon2;
	_battleEnd = false;
	_battleWindow = nullptr;
	_captured = false;
}

void BaseBattle::InitilizeBattleWindow()
{
	_battleWindow = new BattleWindow(_player, _activePokemon1, _activePokemon2);
}


int ExpGain(PokemonGen* p1, PokemonGen* p2) //calculate the exp points based on the two battling pokemon
{
	return static_cast<int>(((p2->BaseExp() * p2->Level()) / (5)) * (pow(2 * p2->Level() + 10, 2.5) / pow(p2->Level() + p1->Level() + 10, 2.5) + 1));
}

BaseBattle::~BaseBattle()
{
	delete _battleWindow;
}

void BaseBattle::PokemonAttack(PokemonGen* attacker, PokemonGen* target, const int selected_move_index)
{
	bool canAttack = true; //variable to track if the pokemon can attack
	if (attacker->Status() == Freeze) //if the pokemon is frozen, determine if it can thaw during this turn
	{
		const int thawChance = rand() % 100;
		if (thawChance < 20) //20% chance of thawing
		{
			*_battleWindow << attacker->Name() + EffectCuringMessage(Freeze);
			attacker->Cure(); //remove the freezing status
			_battleWindow->UpdateStatus(_activePokemon1, _activePokemon2);
		}
		else
		{
			*_battleWindow << attacker->Name() + EffectEmphasisMessage(Freeze); 
			canAttack = false; //pokemon can't attack, still frozen
		}
	}
	if (canAttack)
	{
		attacker->Move(target, selected_move_index, _battleWindow); //use the selected move on the target
		_battleWindow->UpdateStatus(_activePokemon1, _activePokemon2); //update damage, if any on the window
		if (target->Status() == Faint) //if the opposing pokemon has fainted, run the handling function
		{
			PokemonFainted(attacker, target);
		}
	}
}


void BaseBattle::PokemonFainted(PokemonGen* other, PokemonGen* fainted)
{
	_battleWindow->operator<<(fainted->Name() + " has fainted!" + '\n'); //fainting message
	if (other == _activePokemon1) //if the opposing pokemon has fainted
	{
		//calculate the exp gained, and increment the player's pokemon EXP by the calculated amount
		const int expGained = ExpGain(other, fainted); 
		_battleWindow->operator<<(other->Name() + " gained " + std::to_string(expGained) + " exp!");
		other->AddExp(expGained);
		other->AddEVs(fainted->EvYield()); //also increment the player's pokemon Effort values
	}
	_battleWindow->FaintingAnimation(fainted); //play the fainting animation
	_turnEnd = true; //end the turn
	CheckBattleEnd(); //Check if the battle has ended
}


void BaseBattle::BattleLoop()
{
	_battleWindow->BattleStart(); //play the battle starting animation
	_battleWindow->UpdateStatus(_activePokemon1, _activePokemon2);
	while (!_battleEnd) //run until the battle ends
	{
		BattleMenu(); //display the battle menu, and perfrom all subsequent actions
		if (!_battleEnd) //if the battle has not ended after pokemon have attacked
		{
			//apply the effects of any Status conditions the pokemon may have
			//if any pokemon faint as a result of the effects, run the appropriate fainting function
			_activePokemon2->AffectStatus(_battleWindow);
			_battleWindow->UpdateStatus(_activePokemon1, _activePokemon2);
			if (_battleEnd)
			{
				PokemonFainted(_activePokemon1, _activePokemon2);
			}
			else
			{
				_activePokemon1->AffectStatus(_battleWindow);
				_battleWindow->UpdateStatus(_activePokemon1, _activePokemon2);
				if (_battleEnd)
				{
					PokemonFainted(_activePokemon2, _activePokemon1);
				}
			}
		}
	}
}

bool BaseBattle::CheckBattleEnd()
{
	if (_activePokemon2->Status() == Faint) //if the opposing pokemon has fainted
	{
		_battleEnd = true;
		//if the player has space in their pokemon set, add the defeated pokemon to the set
		int i = 0;
		for (PokemonGen* pokemon : _player->PokemonSet())
		{	
			if (pokemon == nullptr)
			{
				_player->PokemonSet()[i] = _activePokemon2;
				_captured = true;
				break;
			}
			++i;
		}
		return true;
	}
	if (_activePokemon1->Status() == Faint) //if the player's pokemon has fainted
	{
		if (CheckOwn()) //check if all of the player's pokemon have fainted
		{
			_battleEnd = true;
			return true;
		}
	}
	return false;
}

bool BaseBattle::CheckOwn()
{
	bool allFainted = true;
	for (PokemonGen* pokemon : _player->PokemonSet()) //loop through the players pokmeon, 
	{
		if (pokemon != nullptr && pokemon->Status() != Faint) //if any pokemon has not fainted
		{
			allFainted = false;
			int selectedPokemon;
			_battleWindow->DisplayPokemonSet(selectedPokemon);
			_activePokemon1 = _player->PokemonSet()[selectedPokemon];
			_battleWindow->Update(_activePokemon1, _activePokemon2);
			*_battleWindow << "Go " + _activePokemon1->Name();
			//switch to the selected pokemon
			break;
		}
	}
	return allFainted;
}

int BaseBattle::OpponentSelectMove() 
{
	std::vector<int> validMoveIndexs; //vector of all move indexes which can be used
	for (int i = 0; i < 4; ++i)
	{
		if (_activePokemon2->Moves()[i] != nullptr && _activePokemon2->Moves().GetPp(i) != 0) //if the move still has PP left, add it to the vector
		{
			validMoveIndexs.push_back(i);
		}
	}
	if (validMoveIndexs.size() != 0) //if there are valid moves
	{
		const int selectedValidMoveIndex = rand() % static_cast<int>(validMoveIndexs.size()); //select and return a random index (wild battles only)
		return validMoveIndexs[selectedValidMoveIndex];
	}
	return -1;

}

void BaseBattle::AttackSequence()
{
	_turnEnd = false;
	const int selectedMoveIndex2 = OpponentSelectMove(); //opposing pokemon's move 
	//display the player pokemon's moves on the battle window, and get the selected index
	int selectedMoveIndex1;
	*_battleWindow << "Which move to use?";
	_battleWindow->DisplayAttackMenu(selectedMoveIndex1);
	Sound::PlayInteractSound();

	//use the two pokemon's speed stat to determine which pokemom will attack first

	bool active1AttackFirst = true; 

	//if a pokemon is paralyzed, its speed stat is halved

	const double act1EffectSpeed = _activePokemon1->Speed() / (_activePokemon1->Status() == Paralysis ? 2.0 : 1.0);
	const double act2EffectSpeed = _activePokemon2->Speed() / (_activePokemon2->Status() == Paralysis ? 2.0 : 1.0);

	if (act1EffectSpeed < act2EffectSpeed)
	{
		active1AttackFirst = false;
	}

	//if both pokemon have the same speed, select the first attacker at random

	else if (act1EffectSpeed == act2EffectSpeed)
	{
		srand(unsigned(time(nullptr)));
		if (rand() % 2 == 1)
		{
			active1AttackFirst = false;
		}
	}
	if (active1AttackFirst)
	{
		PokemonAttack(_activePokemon1, _activePokemon2, selectedMoveIndex1); //active 1 attackes active 2 
		
		if (!_turnEnd)	//if active 2 has not fainted ( turn would have ended )
		{
			PokemonAttack(_activePokemon2, _activePokemon1, selectedMoveIndex2);
		
		}
	}
	else
	{
		PokemonAttack(_activePokemon2, _activePokemon1, selectedMoveIndex2);
		
		if (!_turnEnd)
		{
			PokemonAttack(_activePokemon1, _activePokemon2, selectedMoveIndex1);
			
		}
	}
}

void BaseBattle::SwitchPokemon()
{
	*_battleWindow << "Which Pokemon to switch?";
	int choice = 0;
	_battleWindow->DisplayPokemonSet(choice); //get the choice from the battle window
	Sound::PlayInteractSound();
	//if the choice is not active pokemon, and a pokemon exists at the chosen index

	if (choice != 0 && _player->PokemonSet()[choice] != nullptr)
	{
		//swap the pokemon
		*_battleWindow << "Come back " + _activePokemon1->Name();
		_battleWindow->FaintingAnimation(_activePokemon1);
		_activePokemon1 = _player->PokemonSet()[choice];
	}
	//update the window to reflect the swapping
	_battleWindow->Update(_activePokemon1, _activePokemon2);
	*_battleWindow << "Go! " + _activePokemon1->Name();
	SDL_Delay(1000);
	PokemonAttack(_activePokemon2, _activePokemon1, OpponentSelectMove()); //the other pokemon attacks once the swapping has been made
	
}

void BaseBattle::UseItem()
{
	*_battleWindow << "Which item to use?";
	int choice = 0;
	_battleWindow->DisplayBag(choice); //get the choice from the battle window
	Sound::PlayInteractSound();
	Item* item = _player->PlayerBag()[choice]->stored_item; //get the item from the bag
	if (item->Use(_activePokemon1))		//use the item, and determine if the item has been used successfully
	{
		*_battleWindow << "Player used the " + item->Name() + "!"; 
		_player->PlayerBag().UseItem(choice); //decrement the item quatity in the bag
	}
	else
	{
		*_battleWindow << "It had no effect!";
	}
	_battleWindow->UpdateStatus(_activePokemon1, _activePokemon2); //update the window to reflect any changes
	PokemonAttack(_activePokemon2, _activePokemon1, OpponentSelectMove()); //the other pokemon attacks once the item has been used
	
}

void BaseBattle::Run() //if the battle is a wild battle, the player can escape
{
	Sound::PlayInteractSound();
	*_battleWindow << "Got away safely!";
	_battleEnd = true;

}

const bool& BaseBattle::Captured() const
{
	return _captured;
}

void BaseBattle::BattleMenu()
{
	_battleWindow->operator<<("What will" + _player->GetName() + " do?");
	int choice = 0;
	_battleWindow->DisplayBattleMenu(choice); //get the choice from the battle window
	Sound::PlayInteractSound();
	SDL_Delay(250);
	switch (choice)
	{
	case 0: //player wants to attack
		AttackSequence();
		break;
	case 3: //player wants to switch pokemon
		SwitchPokemon();
		break;
	case 1: //player wants to use item
		UseItem();
		break;
	case 2: //player wants to escape
		Run();
		break;
	default:
		break;
	}
}

