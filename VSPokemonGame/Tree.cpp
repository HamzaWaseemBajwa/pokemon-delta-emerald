#include "Tree.h"

Tree::Tree(SdlSetup* sdl_setup, double* CameraX, double* CameraY, int x ,int y)
{
	trunk = new Sprite(sdl_setup->GetRenderer(), "Resources/Environment/treeBack.png", x, y, 47, 35, CameraX, CameraY, new CollisionRectangle(0,0,47,35));
	crown = new Sprite(sdl_setup->GetRenderer(), "Resources/Environment/treeFront.png", x-13, y-48, 72, 74, CameraX, CameraY, new CollisionRectangle(0,20,72,54));
}



Tree::~Tree()
{
	delete crown;
	delete trunk;
}


void Tree::DrawCrown() const
{
	crown->Draw();
}

void Tree::DrawTrunk() const
{
	trunk->Draw();
}

int Tree::GetX() const
{
	return trunk->GetX();
}

int Tree::GetY() const
{
	return trunk->GetY();
}
