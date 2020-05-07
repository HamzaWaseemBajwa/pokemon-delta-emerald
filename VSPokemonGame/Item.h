#pragma once
#include "PokemonGen.h"

class Item
{
public:
	Item(std::string item_index, std::string name, std::string description, int price);
	void Display() const;
	virtual bool Use(PokemonGen* p) = 0;
	bool Matches(Item* other) const;
	const std::string& Name() const;
	std::string& ItemIndex();

	virtual ~Item();

private:
	std::string _itemIndex;
	std::string _name;
	std::string _description;
	int _price;
};
