#include "TrainerBattle.h"


TrainerBattle::TrainerBattle(Player* player, Trainer* opponent) : BaseBattle(player, opponent->PokemonSet()[0]),
_opponent(opponent)
{
}

void TrainerBattle::InitilizeBattleWindow()
{
	_battleWindow = new BattleWindow(_player, _activePokemon1, _opponent);
}

bool TrainerBattle::CheckBattleEnd()
{
	//end the battle if either the player's or the opponent's spokemon have all fainted
	if (_activePokemon2->Status() == Faint)
	{
		if (CheckOpp())
		{
			_battleEnd = true;
			TrainerBattleEnd(true); //call the trainer end fuction 
			return true;
		}
	}
	if (_activePokemon1->Status() == Faint)
	{
		if (CheckOwn())
		{
			_battleEnd = true;
			TrainerBattleEnd(false); //call the trainer end fuction 
			return true;
		}
	}
	return false;
}

void TrainerBattle::TrainerBattleEnd(const bool victory) const	
{
	//if the player has won, increase the players money by the trainers prize money
	if (victory)
	{
		_player->IncreaseMoney(_opponent->PrizeMoney());
		*_battleWindow << _player->GetName() + " got " + std::to_string(_opponent->PrizeMoney()) + " for winning!";
		_opponent->SetDefeated(); //set opponent to defeated so he cannot be battled again
	}
	else
	{
		//if the player has lost, decrease the player's money by 1/3rd
		_player->DecreaseMoney(static_cast<int>(_player->GetMoney() / 3.0)); 
		*_battleWindow << _player->GetName() + " had to give " + std::to_string(_player->GetMoney() / 3.0) + " for losing!";
		for (PokemonGen* pokemon : _opponent->PokemonSet()) //heal the oppoents pokemon for future battles
		{
			if (pokemon != nullptr)
			{
				pokemon->Restore();
			}
		}
	}
}

bool TrainerBattle::CheckOpp()
{
	//loop through the oponents pokemonset, and find a non-fainted pokemon
	bool allFainted = true;
	for (PokemonGen* pokemon : _opponent->PokemonSet())
	{
		if (pokemon != nullptr && pokemon->Status() != Faint)
		{
			allFainted = false;
			_activePokemon2 = pokemon; //send out the non-fainted pokemon
			_battleWindow->Update(_activePokemon1, _activePokemon2); //update the battle window to refelct the change
			*_battleWindow << _opponent->GetName() + " sent out " + _activePokemon2->Name();
			break;
		}
	}
	return allFainted; //return true if no un-fainted pokemon is found, or false otherwise
}

int TrainerBattle::OpponentSelectMove()
{
	std::vector<std::array<int, 2>> validMoveIndexsAndScores; //a vector of move indexes and their respective scores
	for (int i = 0; i < 4; ++i) //loop through the opponents pokemon's moves
	{
		if (_activePokemon2->Moves()[i] != nullptr && _activePokemon2->Moves().GetPp(i) != 0) //select only those mvoes that have remaining PP
		{
			//the move score is selected on the basis of which move can cause the most damage from the attackers perspective
			int moveScore = 0;
			const PokemonType moveType = _activePokemon2->Moves()[i]->MoveType();
			const double type = TypeEffect(moveType, _activePokemon1->Type1(), _activePokemon1->Type2());
			if (type != 0)
			{
				const int moveCatInt = _activePokemon2->Moves()[i]->MoveCat();
				int offStat = 1;
				if (moveCatInt == 2)
				{
					offStat = 3;
				}
				const int basePower = _activePokemon2->Moves()[i]->Attack()->BasePower();
				double stab = 1.0;
				if (moveType == _activePokemon2->Type1() || moveType == _activePokemon2->Type2())
				{
					stab *= 1.5;
				}
				double burn = 1.0;
				if (moveCatInt == 1 && _activePokemon2->Status() == Burn)
				{
					burn = 0.5;
				}
				const double mod = stab * type * burn;
				moveScore = static_cast<int>(basePower * static_cast<double>(_activePokemon2->BaseStats()[offStat]) * mod);
			}
			validMoveIndexsAndScores.push_back({ i, moveScore });
		}
	}
	if (validMoveIndexsAndScores.size() == 0) //if there is no move that can be used
	{
		return -1;
	}
	if (validMoveIndexsAndScores.size() == 1) //if there is only one valid move
	{
		return validMoveIndexsAndScores[0][0]; //return its index
	}

	//else find the move index with the highest score and return it
	int highestScore = 0;
	int highestScoreIndex = 0;
	for (auto element : validMoveIndexsAndScores)
	{
		if (element[1] > highestScore)
		{
			highestScore = element[1];
			highestScoreIndex = element[0];
		}
	}
	return highestScoreIndex;

}

void TrainerBattle::Run() //deny the oppurtunity to espace from a trianer battle
{
	*_battleWindow << "No! Can't run from a Trainer battle!";
	PokemonAttack(_activePokemon2, _activePokemon1, OpponentSelectMove());
}

TrainerBattle::~TrainerBattle()
{
}
