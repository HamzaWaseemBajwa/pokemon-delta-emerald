#include "Item.h"
#include <iostream>

Item::Item(const std::string item_index, const std::string name, const std::string description, const int price) : _itemIndex(item_index), _name(name), _description(description), _price(price)
{
}

void Item::Display() const
{
	std::cout << _name << "\n<" << _description << ">\n";
}

Item::~Item()
{
	std::cout << "Deleting item" << std::endl;

}

bool Item::Matches(Item* other) const
{
	return this->_name == other->_name;
}

const std::string& Item::Name() const
{
	return _name;
}

std::string& Item::ItemIndex()
{
	return _itemIndex;
}
