#pragma once
#include "Item.h"
class HealHealthItem :
	public virtual Item
{
public:
	HealHealthItem(std::string item_index, std::string name, std::string description, int price);
	HealHealthItem(std::string item_index, std::string name, std::string description, int price, int restored_health);
	int GetHealingAmount() const;
	bool Use(PokemonGen* p) override;
	virtual ~HealHealthItem();
private:
	int _restoredHealth;
};

