#pragma once
#include "Item.h"
class Pokeball :
	public Item
{
public:
	Pokeball(std::string item_index, const std::string name, const std::string description, const int price);
	Pokeball(std::string item_index, const std::string name, const std::string description, const int price, double rate_of_capture);
	bool Use(PokemonGen*) override;
	~Pokeball();

private:
	double _rateOfCapture;
};
