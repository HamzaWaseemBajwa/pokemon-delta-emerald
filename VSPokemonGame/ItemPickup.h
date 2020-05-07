#pragma once
#include "Item.h"
#include "SdlSetup.h"
#include "Sprite.h"

class ItemPickup	//class of pickable item objects in the environment
{
public:
	ItemPickup(SdlSetup* passed_setup, Item* item, const int x, const int y, double* camera_x, double* camera_y);

	Sprite* GetItemSprite() const;

	void Draw() const;

	Item* GetItem() const;

	~ItemPickup();
private:
	SdlSetup* _sdlSetup;
	Item* _item;	//item attached to the sprite
	Sprite* _itemImage;
};

