#pragma once
#include "PokemonGen.h"
#include "Item.h"

class HybridHealItem : public Item
{
public:
	HybridHealItem(std::string item_index, const std::string& name, const std::string& description, int price, bool revives);
	bool Use(PokemonGen* p) override;

	virtual ~HybridHealItem();
private:
	bool _canRevive;
};

