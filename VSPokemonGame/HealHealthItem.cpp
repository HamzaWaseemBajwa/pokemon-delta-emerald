#include "HealHealthItem.h"

HealHealthItem::HealHealthItem(const std::string item_index, const std::string name, const std::string description, const int price) : Item(item_index, name, description, price),
_restoredHealth(0)
{}

HealHealthItem::HealHealthItem(const std::string item_index, const std::string name, const std::string description, const int price, const int restored_health) : Item(item_index, name, description, price), _restoredHealth(restored_health)
{}

int HealHealthItem::GetHealingAmount() const
{
	return _restoredHealth;
}

bool HealHealthItem::Use(PokemonGen* p)
{
	if (p->Status() != Faint)
	{
		if (p->CurrentHp() != p->MaxHp())
		{
			if (_restoredHealth != 0)
			{
				p->Heal(_restoredHealth);
			}
			else
			{
				p->Heal();
			}
			return true;
		}
	}
	return false;
}

HealHealthItem::~HealHealthItem()
{}
