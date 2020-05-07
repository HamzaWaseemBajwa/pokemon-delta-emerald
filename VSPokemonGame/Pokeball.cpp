#include "Pokeball.h"



Pokeball::Pokeball(std::string item_index, const std::string name, const std::string description, const int price): Item(item_index, name, description,price), _rateOfCapture(0)
{
}

Pokeball::Pokeball(std::string item_index, const std::string name, const std::string description, const int price, const double rate_of_capture):
	Item(item_index, name, description, price), _rateOfCapture(rate_of_capture)
{
}

bool Pokeball::Use(PokemonGen*)
{
	return true;
}


Pokeball::~Pokeball()
{
}
