#include "StatusHealItem.h"
#include <iostream>

StatusHealItem::StatusHealItem(const std::string item_index, const std::string name, const std::string description, const int price) : Item(item_index, name, description, price), _curedEffect(NoEffect)
{}

StatusHealItem::StatusHealItem(const std::string item_index, const std::string name, const std::string description, const int price, const StatusEffect cured_effect) : Item(item_index, name, description, price), _curedEffect(cured_effect)
{}

StatusEffect StatusHealItem::GetRestoredEffect() const
{
	return _curedEffect;
}

bool StatusHealItem::Use(PokemonGen* p)
{
	if (p->Status() != NoEffect)
	{
		if ((p->Status() == _curedEffect || _curedEffect == NoEffect) && p->Status() != Faint)
		{
			p->Cure();
			return true;
		}
	}
	std::cout << "It did not have any affect\n";
	return false;

}

StatusHealItem::~StatusHealItem()
{
}
