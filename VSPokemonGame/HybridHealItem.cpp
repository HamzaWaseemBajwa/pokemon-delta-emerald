#include "HybridHealItem.h"

HybridHealItem::HybridHealItem(const std::string item_index, const std::string& name, const std::string& description, const int price,
	const bool revives) : Item(item_index, name, description, price), _canRevive(revives)
{
}

bool HybridHealItem::Use(PokemonGen* p)
{
	if (p->Status() != NoEffect)
	{
		if (p->Status() == Faint)
		{
			if (_canRevive)
			{
				p->Cure();
				p->Heal();
				return true;
			}
			return false;
		}
		p->Cure();
		return true;
	}
	if (p->CurrentHp() < p->MaxHp())
	{
		p->Heal();
		return true;
	}
	return false;
}

HybridHealItem::~HybridHealItem()
{
}
