#pragma once
#include "ItemQuantity.h"
#include <vector>

class Bag
{
public:
	Bag();
	void AddItem(Item* added_item);
	void AddItem(Item* added_item, const int amount);
	void UseItem(int item_index);
	int GetItemIndex(Item* item);
	ItemQuantity* operator[](const int index);
	int Size() const;
	void Display();

	~Bag();
private:
	std::vector<ItemQuantity*> _bagItems;
};