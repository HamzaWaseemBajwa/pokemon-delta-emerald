#include "PokemonGen.h"
#include "BattleWindow.h"
#include <iostream>
#include "Sound.h"

PokemonGen::PokemonGen(PokemonBase b, const int level, const PokemonNature nature, const std::array<int, 6>& ev_spread, const std::array<int, 6>& iv_spread, const MoveSet m) : 
	PokemonBase(
		b.GetIndexNo(),
		b.Name(),
		b.Type1(),
		b.Type2(),
		b.BaseStats(),
		b.GrowthRate(),
		b.CatchRate(),
		b.EvYield(),
		b.BaseExp(),
		b.GetImagePath()),
	_level(level),
	_status(NoEffect),
	_exp(ExpAtLevel(level)),
	_nature(nature),
	_evSpread(ev_spread),
	_ivSpread(iv_spread),
	_moves(m)
{
	_currentHp = MaxHp();
}

PokemonGen::PokemonGen(PokemonBase b, const int level, const MoveSet m) :
	PokemonBase(
		b.GetIndexNo(),
		b.Name(),
		b.Type1(),
		b.Type2(),
		b.BaseStats(),
		b.GrowthRate(),
		b.CatchRate(),
		b.EvYield(),
		b.BaseExp(),
		b.GetImagePath()),
	_level(level),
	_status(NoEffect),
	_exp(ExpAtLevel(level)),
	_nature(static_cast<PokemonNature>(rand() % 25)),
	_evSpread({ 0, 0, 0, 0, 0, 0 }),
	_ivSpread({ rand() % 32 , rand() % 32 , rand() % 32 , rand() % 32 , rand() % 32 ,rand() % 32 }),
	_moves(m)
{
	_currentHp = MaxHp();
}

PokemonGen::PokemonGen(PokemonBase b, const int level, const int current_hp, const StatusEffect status, const int exp, const PokemonNature nature, const std::array<int, 6>& ev_spread, const std::array<int, 6>& iv_spread, const MoveSet m) :
	PokemonBase(
		b.GetIndexNo(),
		b.Name(),
		b.Type1(),
		b.Type2(),
		b.BaseStats(),
		b.GrowthRate(),
		b.CatchRate(),
		b.EvYield(),
		b.BaseExp(),
		b.GetImagePath()),
	_level(level),
	_currentHp(current_hp),
	_status(status),
	_exp(exp),
	_nature(nature),
	_evSpread(ev_spread),
	_ivSpread(iv_spread),
	_moves(m)
{}

std::string ConvertArrayToString(std::array<int, 6> array)
{
	std::string arrayString;
	for (int i = 0; i < 6; ++i)
	{
		arrayString += std::to_string(array[i]);
		if (i != 5)
		{
			arrayString += ':';
		}
	}
	return arrayString;
}

std::string PokemonGen::ToString()
{
	std::string pokemonString = "<Pokemon>\n"
		+ GetIndexNo()
		+ ',' + std::to_string(_level)
		+ ',' + std::to_string(_currentHp)
		+ ',' + std::to_string(static_cast<int>(_status))
		+ ',' + std::to_string(_exp)
		+ ',' + std::to_string(static_cast<int>(_nature))
		+ ',' + ConvertArrayToString(_evSpread)
		+ ',' + ConvertArrayToString(_ivSpread) + '\n'
		+ _moves.ToString() + '\n'
		+ "</Pokemon>";
	return pokemonString;
}


int PokemonGen::CalculateStat(const int stat)	//stat calculation fomula
{
	return static_cast<int>(((2 * BaseStats()[stat] + _ivSpread[stat] + _evSpread[stat] / 4) * _level / 100 + 5) *
		Nature(stat, _nature));
}

void PokemonGen::LevelUp()	//Increase level and change stats
{
	std::array<int, 6> tempPreStats = { MaxHp(), Attack(), Defense(), SpAttack(), SpDefense(), Speed() };
	_level++;
	std::array<int, 6> tempPostStats = { MaxHp(), Attack(), Defense(), SpAttack(), SpDefense(), Speed() };
	std::cout << Name() << " grew to Lv. " << _level << "!" << '\n';
	for (int i = 0; i < 6; i++)
	{
		std::cout << to_string(static_cast<Stat>(i)) << ": +";
		std::cout << tempPostStats[i] - tempPreStats[i] << '\n';
	}
}


int PokemonGen::MaxHp()	//calculate HP
{
	return (2 * BaseStats()[0] + _ivSpread[0] + _evSpread[0] / 4) * _level / 100 + _level + 10;
}

void PokemonGen::Damage(const int damage)	
{
	if (_currentHp > damage)	//if damage is more than remaning HP, cause fainting 
	{
		_currentHp -= damage;
	}
	else
	{
		_currentHp = 0;
		_status = Faint;
	}
}

void PokemonGen::Heal()	
{
	_currentHp = MaxHp();
}

void PokemonGen::Heal(const int restored_hp)	//heal by passed amount
{
	if (_currentHp + restored_hp >= MaxHp())
	{
		_currentHp = MaxHp();
	}
	else
	{
		_currentHp += restored_hp;
	}
}

void PokemonGen::Cure()
{
	_status = NoEffect;
}

void PokemonGen::Revive()
{
	Cure();
	Heal();
}

void PokemonGen::Restore()
{
	Revive();
	_moves.RestorePp();
}

int PokemonGen::Level() const
{
	return _level;
}

int PokemonGen::Attack()
{
	return CalculateStat(1);
}

int PokemonGen::Defense()
{
	return CalculateStat(2);
}

int PokemonGen::SpAttack()
{
	return CalculateStat(3);
}

int PokemonGen::SpDefense()
{
	return CalculateStat(4);
}

int PokemonGen::Speed()
{
	return CalculateStat(5);
}


void PokemonGen::AddExp(int exp)	//add exp points
{
	if (_level == 100)	//if level is 100, do not add more exp points
	{
		exp = 0;
	}
	else if (exp >= ExpAtLevel(_level + 1) - _exp)	//if passed exp point are enough for a level up, loop until remaining exp are less than needed for level up
	{
		int remaining = exp;
		while (remaining > 0)
		{
			remaining -= ExpAtLevel(_level + 1) - _exp;
			_exp += ExpAtLevel(_level + 1) - _exp;
			LevelUp();
			if (_level == 100)
			{
				exp = 0;
			}
			else if (remaining < ExpAtLevel(_level + 1) - _exp)
			{
				exp = remaining;
				remaining = 0;
			}
		}
	}
	_exp += exp;
}


void PokemonGen::Display()
{
	std::cout << "Name: " << Name() << '\n'
		<< "Level: " << _level << '\n'
		<< "HP: " << _currentHp << " / " << MaxHp() << '\n'
		<< "Status: " << to_string(_status) << '\n'
		<< "EXP: " << _exp << '\n'
		<< "To next level: " << ExpToNextLevel() << '\n';
}

void PokemonGen::ShowMoves()
{
	_moves.DisplayMoves();
}

void PokemonGen::Move(PokemonGen* target, const int selected_move_index, BattleWindow* battle_window)
{
	PokemonMove* selectedMove = _moves[selected_move_index];
	*battle_window << Name() + " used " + selectedMove->Name() + "!";
	SDL_Delay(500);
	const int accuracy = rand() % 100 + 1;	//calcualte accuracy of using move
	if (accuracy <= selectedMove->Accuracy())	//if accuray is less than that of move, use successfuly
	{
		if (selectedMove->Attack() != nullptr) //if move has an attacking component
		{
			//calculate move damage using formula

			const PokemonType moveType = selectedMove->MoveType();
			const double type = TypeEffect(moveType, target->Type1(), target->Type2());
			if (type == 0)	//if pokemon is immune to the move
			{
				*battle_window << "It had no effect...";
			}
			else
			{
				battle_window->AttackAnimation(this);
				const int moveCatInt = selectedMove->MoveCat();
				int offStat = 1;
				if (moveCatInt == 2)
				{
					offStat = 3;
				}
				const int basePower = selectedMove->Attack()->BasePower();
				const double rnd = ((rand() % 16) + 85) / 100.0;
				double stab = 1.0;
				if (moveType == Type1() || moveType == Type2())
				{
					stab *= 1.5;
				}
				double burn = 1.0;
				if (moveCatInt == 1 && _status == Burn)
				{
					burn = 0.5;
				}
				const double mod = rnd * stab * type * burn;
				const int damage = static_cast<int>(((2 * _level / 5.0 + 2) * basePower * (static_cast<double>(BaseStats()[offStat])/static_cast<double>(target->BaseStats()[offStat + 1])) / 50.0 + 2) * mod);
				target->Damage(damage);	//reduce target's Hp by damage amount
				if (type > 1)
				{
					*battle_window << "Its super effective!";
					Sound::PlaySound("SuperEffective");
				}
				else if (type < 1)
				{
					*battle_window << "Its not very effective!";
					Sound::PlaySound("NotVeryEffective");
				}
				else
				{
					Sound::PlaySound("Normal");
				}
				
			}
		}
		if (target->CurrentHp() != 0)	//if the target has not fainted
		{
			if (selectedMove->Status() != nullptr)	//if the move has a status effect component
			{
				if (target->Status() == NoEffect)	//if the target does not already have a status effect
				{
					const int chance = rand() % 101;	//calculate chance of the effect being applied
					if (chance < selectedMove->Status()->GetEffectChance())		//compare the calcualed chance to the movses chance
					{
						target->SetStatus(selectedMove->Status()->GetEffect());	//apply the status effect
						*battle_window << target->Name() + EffectAppliedMessage(target->Status());
					}
				}
			}
		}
	}
	else
	{
		*battle_window << "It missed!";
	}
	_moves.UseMove(selected_move_index);//reduce the used moves PP
}

void PokemonGen::AddEVs(std::array<int, 6> yield)	//function to Add Effort values to pokemon after a defeating an opponent
{
	//every pokemon has a certain yield of EV that it passes after being defeated
	//total evs that can be gained are 510
	//maximum evs for each stat are 256

	int evSum = 0;
	for (int i = 0; i < 6; ++i)
	{
		evSum += _evSpread[i];
	}
	if (evSum < 510)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (evSum < 510)
			{
				if (_evSpread[i] + yield[i] <= 256)
				{
					_evSpread[i] += yield[i];
					evSum += yield[i];
				}
				else
				{
					evSum += 256 - _evSpread[i];
					_evSpread[i] = 256;
				}
			}
		}
	}
}


int PokemonGen::ExpAtLevel(const int level) const	//calcualte the exp of the pokemon at the passed level, according to the growth rate
{
	if (level == 1) { return 0; }
	double exp = 0;
	switch (GrowthRate())
	{
	case Erratic:
		if (level <= 50)
		{
			exp = (pow(level, 3.0) * (100.0 - level)) / 50.0;
		}
		else if (level > 50 && level <= 68)
		{
			exp = (pow(level, 3.0) * (150.0 - level)) / 100.0;
		}
		else if (level > 68 && level <= 98)
		{
			exp = (pow(level, 3.0) * ((1911.0 - 10.0 * level) / 3)) / 500.0;
		}
		else
		{
			exp = (pow(level, 3.0) * (160.0 - level)) / 100.0;
		}
		break;
	case Fast:
		exp = (4.0 * pow(level, 3.0)) / 5.0;
		break;
	case MediumFast:
		exp = pow(level, 3);
		break;
	case MediumSlow:
		exp = (6.0 / 5.0) * pow(level, 3.0) - 15.0 * pow(level, 2.0) + 100.0 * level - 140;
		break;
	case Slow:
		exp = (5.0 * pow(level, 3.0)) / 4.0;
		break;
	case Fluctuating:
		if (level <= 15)
		{
			exp = pow(level, 3.0) * ((((level + 1.0) / 3.0) + 24.0) / 50.0);
		}
		else if (level > 15 && level <= 36)
		{
			exp = pow(level, 3.0) * ((level + 14.0) / 50.0);
		}
		else
		{
			exp = pow(level, 3.0) * (((level / 2.0) + 32.0) / 50.0);
		}
		break;
	default:;
	}
	return static_cast<int>(exp);
}

int PokemonGen::ExpAtLevel() const //return exp at the current level
{
	return ExpAtLevel(_level);
}

int PokemonGen::ExpToNextLevel() const	//calculaate exp to reach next level
{
	return (ExpAtLevel(_level + 1) - _exp);
}

int PokemonGen::CurrentHp() const
{
	return _currentHp;
}

StatusEffect PokemonGen::Status() const
{
	return _status;
}

MoveSet& PokemonGen::Moves()
{
	return _moves;
}

void PokemonGen::SetStatus(const StatusEffect s)
{
	_status = s;
}

void PokemonGen::AffectStatus(BattleWindow* battle_window)
{
	switch (_status)
	{
	case Poisoning:	//poisoning and burn causes damage
	case Burn:
		*battle_window << Name() + EffectEmphasisMessage(_status);
		Damage(MaxHp() * 1 / 8);
		break;
	case Freeze:
	case Sleep:
	case NoEffect:
	case Paralysis:
	case Faint:
	default:
		break;
	}
}
