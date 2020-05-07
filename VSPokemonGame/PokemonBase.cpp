#include "PokemonBase.h"
#include <sstream>

std::array<int, 6> ConvertToArray(const std::string stat_string) //helper function for converting stat string to stat array
{
	std::stringstream sStream(stat_string); //covert string to stream
	std::string stat;
	std::array<int, 6> statArray = { 0, 0, 0, 0, 0 ,0 };
	int i = 0;
	while (getline(sStream, stat, ':')) //split by ':' character
	{
		statArray[i] = stoi(stat);
		i++;
	}
	return statArray;
}

PokemonBase::PokemonBase(const std::string index_no, const std::string& pokemon_name, const PokemonType pokemon_type1, const PokemonType pokemon_type2,
	const std::array<int, 6>& base_stats, const ::GrowthRate growth_rate, const int catch_rate,
	const std::array<int, 6>& ev_yield, const int base_exp, const std::string no) :
	_indexNo(index_no),
	_pokemonName(pokemon_name),
	_pokemonType1(pokemon_type1),
	_pokemonType2(pokemon_type2),
	_baseStats(base_stats),
	_growthRate(growth_rate),
	_catchRate(catch_rate),
	_evYield(ev_yield),
	_baseExp(base_exp),
	_imagePath(no)
{}

PokemonBase::PokemonBase(std::array<std::string, 10> pokemon_data) :
	_indexNo(pokemon_data[0]),
	_pokemonName(pokemon_data[1]),
	_pokemonType1(static_cast<PokemonType>(stoi(pokemon_data[2]))),
	_pokemonType2(static_cast<PokemonType>(stoi(pokemon_data[3]))),
	_baseStats(ConvertToArray(pokemon_data[4])),
	_growthRate(static_cast<::GrowthRate>(stoi(pokemon_data[5]))),
	_catchRate(stoi(pokemon_data[6])),
	_evYield(ConvertToArray(pokemon_data[7])),
	_baseExp(stoi(pokemon_data[8])),
	_imagePath(pokemon_data[9])
{}

PokemonBase::PokemonBase() :
	_pokemonName(""),
	_pokemonType1(None),
	_pokemonType2(None),
	_baseStats(),
	_growthRate(),
	_catchRate(0), 
	_evYield(),
	_baseExp(0),
	_imagePath("")
{}

const std::string& PokemonBase::GetIndexNo() const
{
	return _indexNo;
}

const std::string& PokemonBase::Name() const
{
	return _pokemonName;
}

PokemonType PokemonBase::Type1() const
{
	return _pokemonType1;
}

PokemonType PokemonBase::Type2() const
{
	return _pokemonType2;
}

const std::array<int, 6>& PokemonBase::BaseStats() const
{
	return _baseStats;
}

GrowthRate PokemonBase::GrowthRate() const
{
	return _growthRate;
}

int PokemonBase::CatchRate() const
{
	return _catchRate;
}

const std::array<int, 6>& PokemonBase::EvYield() const
{
	return _evYield;
}

int PokemonBase::BaseExp() const
{
	return _baseExp;
}

const std::string& PokemonBase::GetImagePath() const
{
	return _imagePath;
}
