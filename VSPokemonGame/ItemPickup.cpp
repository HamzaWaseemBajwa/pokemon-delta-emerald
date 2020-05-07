#include "ItemPickup.h"



//ItemSprite::ItemSprite()
//{
//}
//
//
//ItemSprite::~ItemSprite()
//{
//}
ItemPickup::ItemPickup(SdlSetup* passed_setup, Item* item, const int x, const int y, double* camera_x, double* camera_y)
{
	_sdlSetup = passed_setup;
	_item = item;
	_itemImage = new Sprite(_sdlSetup->GetRenderer(), "Resources/Environment/itemPickup.png", x, y, 32, 32, camera_x,
	                        camera_y, new CollisionRectangle(4, 4, 24, 24));
}

Sprite* ItemPickup::GetItemSprite() const
{
	return _itemImage;
}

void ItemPickup::Draw() const
{
	_itemImage->Draw();
}

Item* ItemPickup::GetItem() const
{
	return _item;
}

ItemPickup::~ItemPickup()
{
	delete _itemImage;
}
