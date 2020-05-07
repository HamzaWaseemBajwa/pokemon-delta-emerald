#pragma once

#include <array>
#include "enums.h"
#include <string>

std::array<int, 6> ConvertToArray(const std::string stat_string);

class PokemonBase
{
public:
	PokemonBase(); //default ctor

	PokemonBase(std::string index_no, const std::string &pokemon_name, PokemonType pokemon_type1, PokemonType pokemon_type2,
		const std::array<int, 6> &base_stats, GrowthRate growth_rate, int catch_rate, const std::array<int, 6> &ev_yield,
		int base_exp, std::string no); //ctor 1

	explicit PokemonBase(std::array<std::string, 10>); //ctor for file reading


	const std::string& GetIndexNo() const;

	const std::string &Name() const;

	PokemonType Type1() const;

	PokemonType Type2() const;

	const std::array<int, 6> &BaseStats() const;

	GrowthRate GrowthRate() const;

	int CatchRate() const;

	const std::array<int, 6> &EvYield() const;

	int BaseExp() const;

	const std::string& GetImagePath() const;

	virtual ~PokemonBase() = default;
private:
	std::string _indexNo; 
	std::string _pokemonName;
	PokemonType _pokemonType1;
	PokemonType _pokemonType2;
	std::array<int, 6> _baseStats; 
	::GrowthRate _growthRate;
	int _catchRate;
	std::array<int, 6> _evYield;
	int _baseExp;
	std::string _imagePath;
};

