#pragma once
#include "Item.h"
#include <iostream>

struct ItemQuantity 
{
	explicit ItemQuantity(Item* item) : stored_item(item), quantity(1)
	{}
	ItemQuantity(Item* item, const int amount) : stored_item(item), quantity(amount)
	{}
	Item* stored_item;
	int quantity;
	void Display() const
	{
		stored_item->Display();
		std::cout << 'x' << quantity << '\n';
	}
	~ItemQuantity()
	{}
};

