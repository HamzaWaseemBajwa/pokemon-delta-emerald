#pragma once

#include <string>

enum Stat //Enumeration for Pokemon Stat Indexes
{
	HP = 0,
	Attack = 1,
	Defense = 2,
	SpAttack = 3,
	SpDefense = 4,
	Speed = 5
};

std::string to_string(Stat stat); //Converts Stat Enum to Stat Name

enum GrowthRate //Enumeration for Pokemon Growth Rates
{
	Erratic = 0,
	Fast = 1,
	MediumFast = 2,
	MediumSlow = 3,
	Slow = 4,
	Fluctuating = 5,
};


enum StatusEffect //Enumeration for Pokemon Status Effects, including fainting
{
	NoEffect = 0,
	Paralysis = 1,
	Poisoning = 2,
	Burn = 3,
	Sleep = 4,
	Freeze = 5,
	Faint = 6
};


std::string to_string(StatusEffect effect); //Converts effect enum to Effect Name

std::string EffectAppliedMessage(StatusEffect effect); //Prints message when effect is applied

std::string EffectEmphasisMessage(StatusEffect effect); //Prints message when effect has emphasis during battle

std::string EffectCuringMessage(const StatusEffect effect); //Prints message when effect is cured


enum PokemonType //Enumeration for Pokemon Types
{
	Normal = 0,
	Fire = 1,
	Water = 2,
	Electric = 3,
	Grass = 4,
	Ice = 5,
	Fighting = 6,
	Poison = 7,
	Ground = 8,
	Flying = 9,
	Psychic = 10,
	Bug = 11,
	Rock = 12,
	Ghost = 13,
	Dragon = 14,
	Dark = 15,
	Steel = 16,
	None = 17
};

std::string to_string(PokemonType type); //Convert type enum to type name

double TypeEffect(PokemonType attack, PokemonType def1, PokemonType def2); //calculate type effect multiplier for attack type on defensive type combination

enum PokemonNature //Enumeration for Pokemon Natures
{
	Hardy = 0,
	Lonely = 1,
	Brave = 2,
	Adamant = 3,
	Naughty = 4,
	Bold = 5,
	Docile = 6,
	Relaxed = 7,
	Impish = 8,
	Lax = 9,
	Timid = 10,
	Hasty = 11,
	Serious = 12,
	Jolly = 13,
	Naive = 14,
	Modest = 15,
	Mild = 16,
	Quiet = 17,
	Bashful = 18,
	Rash = 19,
	Calm = 20,
	Gentle = 21,
	Sassy = 22,
	Careful = 23,
	Quirky = 24
};

inline std::string to_string(PokemonNature _nature); //Convert nature enum to nature name

double Nature(int stat, PokemonNature _nature); //calculates effect of pokemon nature on stat

enum MoveCategory //Enumeration for Pokemon move categories
{
	Status = 0,
	Physical = 1,
	Special = 2,
};

inline std::string to_string(MoveCategory cat); //Convert category enum to string 