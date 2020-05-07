#include "PokemonMove.h"
#include <array>

//attack_effect, causes direct damage to Pokemon

AttackEffect::AttackEffect(const int base_power, const MoveCategory category) : _basePower(base_power), _category(category)
{}

int AttackEffect::BasePower() const
{
	return _basePower;
}

MoveCategory AttackEffect::Category() const
{
	return _category;
}

//status_effect, causes a status condition to Pokemon

StatusChange::StatusChange(const StatusEffect effect, const int effect_chance) : _effect(effect), _effectChance(effect_chance)
{}

StatusEffect StatusChange::GetEffect() const
{
	return _effect;
}

int StatusChange::GetEffectChance() const
{
	return _effectChance;
}

//PokemonMove

PokemonMove::PokemonMove(const std::string &index, const std::string &name, const int accuracy, const int base_pp, const PokemonType move_type,
	AttackEffect* atk_e, StatusChange* status_e) :
	_moveIndex(index),
	_name(name),
	_accuracy(accuracy),
	_basepp(base_pp),
	_moveType(move_type),
	_atkE(atk_e),
	_statusE(status_e)
{}

PokemonMove::PokemonMove(std::array<std::string, 10> move_data) :
	_moveIndex(move_data[0]),
	_name(move_data[1]),
	_accuracy(stoi(move_data[2])),
	_basepp(stoi(move_data[3])),
	_moveType(static_cast<PokemonType>(stoi(move_data[4]))),
	_atkE(new AttackEffect(stoi(move_data[5]), static_cast<MoveCategory>(stoi(move_data[6]))))
{
	if (move_data[7] != "NULL")
	{
		_statusE = new StatusChange(static_cast<StatusEffect>(stoi(move_data[7])), stoi(move_data[8]));
	}
	else
	{
		_statusE = nullptr;
	}
}

PokemonMove::~PokemonMove()
{
	delete _atkE;
	delete _statusE;
}

int PokemonMove::BasePp() const
{
	return _basepp;
}

std::string PokemonMove::Name() const
{
	return _name;
}

PokemonType PokemonMove::MoveType() const
{
	return _moveType;
}

int PokemonMove::MoveCat() const
{
	if (_atkE != nullptr) //if move has an attack component return its category, othewise return as "Status"
	{
		return _atkE->Category();
	}
	return 0;
}

AttackEffect* PokemonMove::Attack() const
{
	return _atkE;
}

StatusChange* PokemonMove::Status() const
{
	return _statusE;
}

std::string PokemonMove::GetIndex() const
{
	return _moveIndex;
}

int& PokemonMove::Accuracy()
{
	return _accuracy;
}
