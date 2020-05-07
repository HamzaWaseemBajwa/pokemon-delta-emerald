#pragma once
#include "Item.h"
class StatusHealItem :
	public virtual Item
{
public:
	StatusHealItem(std::string item_index, std::string name, std::string description, int price);
	StatusHealItem(std::string item_index, std::string name, std::string description, int price, StatusEffect cured_effect);
	StatusEffect GetRestoredEffect() const;
	bool Use(PokemonGen* p) override;
	virtual ~StatusHealItem();
private:
	StatusEffect _curedEffect;
};

