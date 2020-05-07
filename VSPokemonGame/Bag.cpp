#include "Bag.h"
#include <iostream>

Bag::Bag()
{
}

void Bag::AddItem(Item* added_item)
{
	bool found = false;
	for (std::vector<ItemQuantity*>::iterator i = _bagItems.begin(); i != _bagItems.end(); ++i)
	{
		if ((*i)->stored_item->Matches(added_item))
		{
			found = true;
			(*i)->quantity++;
			i = _bagItems.end();
			break;
		}
	}
	if (!found)
	{
		_bagItems.push_back(new ItemQuantity{added_item});
	}
}

void Bag::AddItem(Item* added_item, const int amount)
{
	bool found = false;
	for (std::vector<ItemQuantity*>::iterator i = _bagItems.begin(); i != _bagItems.end(); ++i)
	{
		if ((*i)->stored_item->Matches(added_item))
		{
			found = true;
			(*i)->quantity += amount;
			i = _bagItems.end() - 1;
		}
	}
	if (!found)
	{
		_bagItems.push_back(new ItemQuantity{added_item, amount});
	}
}

void Bag::UseItem(const int item_index)
{
	_bagItems[item_index]->quantity--;
	if (_bagItems[item_index]->quantity == 0)
	{
		delete _bagItems[item_index];
		_bagItems.erase(_bagItems.begin() + item_index);
	}
}

int Bag::GetItemIndex(Item* item)
{
	int index = 0;
	std::vector<ItemQuantity*>::iterator i = _bagItems.begin();
	while (i != _bagItems.end())
	{
		if ((*i)->stored_item->Matches(item))
		{
			return index;
		}
		++index;
		++i;
	}
	return -1;
}

ItemQuantity* Bag::operator[](const int index)
{
	return _bagItems[index];
}

int Bag::Size() const
{
	return static_cast<int>(_bagItems.size());
}

void Bag::Display()
{
	int index = 0;
	for (std::vector<ItemQuantity*>::iterator i = _bagItems.begin(); i != _bagItems.end(); ++i)
	{
		std::cout << '[' << index << "] ";
	
		(*i)->Display();
		std::cout << '\n';
		++index;
	}
}

Bag::~Bag()
{
	for (std::vector<ItemQuantity*>::iterator i = _bagItems.begin(); i != _bagItems.end(); ++i)
	{
		delete (*i);
	}
	_bagItems.clear();
}
