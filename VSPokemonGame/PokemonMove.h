#pragma once
#include <string>
#include "enums.h"

class AttackEffect //Class for storing the Damage component of moves
{
public:
	explicit AttackEffect(int base_power, MoveCategory category); //ctor
	//getters
	int BasePower() const; 
	MoveCategory Category() const;
private:
	int _basePower;	//base attack power of move
	MoveCategory _category; //offensive move category, defined in "Enums.h"
};

class StatusChange //Class for storing the Status affecting component of moves
{
public:
	StatusChange(StatusEffect effect, int effect_chance); //ctor
	//getters
	StatusEffect GetEffect() const; 
	int GetEffectChance() const;
private:
	StatusEffect _effect;	//status effect caused by move, defined in "Enums.h"
	int _effectChance;	//probability out of 100 of effect to br applied
};

class PokemonMove //Pokemon Move Class, stores either one or both of the two components
{
public:
	PokemonMove(const std::string &index, const std::string &name, int accuracy, int base_pp, PokemonType move_type, AttackEffect* atk_e, StatusChange* status_e); //ctor

	explicit PokemonMove(std::array<std::string, 10> move_data); //ctor for file read data

	~PokemonMove(); //dtor

	//getters
	int BasePp() const;
	std::string Name() const;
	PokemonType MoveType() const;
	int MoveCat() const;
	AttackEffect* Attack() const;
	StatusChange* Status() const;
	std::string GetIndex() const;
	int& Accuracy();

private:
	std::string _moveIndex; //unique index of move
	std::string _name; //name of move
	int _accuracy; //chance for move to hit out of 100
	int _basepp; //maximum number of times a move can be used before requiring recharge
	PokemonType _moveType; //Type of move, defined in "Enums.h"
	AttackEffect* _atkE; //attack effect of move
	StatusChange* _statusE; //status effect of move
};

