#pragma once
#include "BaseBattle.h"
#include "Trainer.h"

class TrainerBattle : public BaseBattle	//Class to handle battle's with other trainers
{
public:
	TrainerBattle(Player* player, Trainer* opponent);	//ctor, takes player and opponen trainer
	void InitilizeBattleWindow() override; //start battle window
	bool CheckBattleEnd() override; //checks whether battle has ended
	void TrainerBattleEnd(const bool victory) const; //run when a trianer battle has ended, passing whether the player is victorious or not
	bool CheckOpp(); //CHecks whethr the opponents Pokemon have all fainted 
	int OpponentSelectMove() override; //Overriding method for opponent move selection
	void Run() override; //Overriding method for escaping from trainer battles
	~TrainerBattle();

private:
	Trainer* _opponent;
};

