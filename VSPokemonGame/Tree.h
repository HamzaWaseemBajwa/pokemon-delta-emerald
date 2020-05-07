#pragma once
#include "SdlSetup.h"
#include "Sprite.h"

class Tree
{
public:
	Tree(SdlSetup* sdl_setup, double* CameraX, double* CameraY, int x, int y);
	~Tree();
	void DrawCrown() const;
	void DrawTrunk() const;
	int GetX() const;
	int GetY() const;

	Sprite* const& get_trunk() const
	{
		return trunk;
	}

	Sprite* const& get_crown() const
	{
		return crown;
	}
private:
	Sprite* trunk;
	Sprite* crown;
};
