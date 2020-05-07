#pragma once
#include "PokemonBase.h"
#include "MoveSet.h"

class BattleWindow; //forward declaration for use in display

class PokemonGen : public PokemonBase
{
public:
	PokemonGen(PokemonBase b, int level, PokemonNature nature, const std::array<int, 6> &ev_spread,
		const std::array<int, 6> &iv_spread, MoveSet m); //ctor 1

	PokemonGen(PokemonBase b, int level, MoveSet m); //ctor 2

	PokemonGen(PokemonBase b, int level, int currentHp, StatusEffect status, int exp, PokemonNature nature,
		const std::array<int, 6>& ev_spread,
		const std::array<int, 6>& iv_spread, MoveSet m); //ctor 3


	std::string ToString(); //convert pokemon data to file writable string

	int MaxHp(); //return maximum HP
	int Level() const; //return curretn Level

	//Stat getters

	int CurrentHp() const;
	int Attack(); 
	int Defense();
	int SpAttack();
	int SpDefense();
	int Speed();
	
	StatusEffect Status() const; //return current status 
	
	MoveSet& Moves(); //Get moveset

	//battle functions

	void Damage(const int damage); //reduce HP by amount
	void Heal(); //Heal to full HP
	void Heal(const int restored_hp); //Heal HP by amount
	void Cure(); //Remove Status effect
	void Revive(); //Remove fainting and heal to full HP
	void Restore(); //Revive and maximize move PPs
	void SetStatus(StatusEffect s); //set status effect to given effect
	void AffectStatus(BattleWindow* battle_window); //cause effect, and display result to passed battle window
	void Display(); //display battle data to console
	void ShowMoves(); //display moves data to console
	void Move(PokemonGen* target, const int selected_move_index, BattleWindow* battle_window); //use selected move on passed target pokemon, display on passed battle window
	void AddExp(int exp); //add gained experience points
	void AddEVs(std::array<int, 6> yield); //add post battle Effort Values

private:
	int _level;
	int _currentHp;
	StatusEffect _status;
	int _exp;
	PokemonNature _nature;
	std::array <int, 6> _evSpread;
	std::array <int, 6> _ivSpread;
	MoveSet _moves;

	int CalculateStat(int stat); //Calcualte integer value of passed stat
	void LevelUp(); //Level Up pokemon by 1
	int ExpAtLevel(int level) const; //Calculate EXP of pokemon at passed level
	int ExpAtLevel() const; //Calculate EXP of pokemon at current level
	int ExpToNextLevel() const; //Calculate required EXP to reach net level
};
