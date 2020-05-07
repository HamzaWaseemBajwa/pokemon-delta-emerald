#include "Enviroment.h"
#include <fstream>
#include <sstream>
#include "Zone.h"
#include <iostream>

extern std::vector<PokemonBase> pokemon_list;
extern std::vector<PokemonMove*> move_list;
extern std::vector<Item*> item_list;

Enviroment::Enviroment(SdlSetup* p_sdl_setup, const int p_screenWidth, const int p_screenHeight, double* p_CameraX, double* p_CameraY)
{
	_sdlSetup = p_sdl_setup;

	_screenWidth = p_screenWidth;
	_screenHeight = p_screenHeight;

	_cameraX = p_CameraX;
	_cameraY = p_CameraY;


	_dimensions[0] = 0;
	_dimensions[1] = 0;

	LoadEnivroment(); //Load the environment
	
	//add four zones to the zone vector

	_noZone = new Zone(_sdlSetup, 0, 0, 0, 0, _cameraX, _cameraY, "Moving...");
	_zones.push_back(new  Zone(_sdlSetup, 0, 0, 2100, 1700, _cameraX, _cameraY, "Rusturbo City"));
	_zones.push_back(new Zone(_sdlSetup, 0, 1700, 2100, 1000, _cameraX, _cameraY, "Route 04"));
	_zones.push_back(new Zone(_sdlSetup, 0, 2700, 4000, 1300, _cameraX, _cameraY, "Route 05"));
	_zones.push_back(new Zone(_sdlSetup, 2100, 0, 1900, 2700, _cameraX, _cameraY, "East Zone"));

	//add the four edge borders

	_borders.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/colRect.png", 0, 0, 4000, 390, _cameraX, _cameraY, new CollisionRectangle(0, 0, 4000, 390)));
	_borders.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/colRect.png", 3570, 0, 430, 4000, _cameraX, _cameraY, new CollisionRectangle(0, 0, 430, 4000)));
	_borders.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/colRect.png", 0, 0, 400, 4000, _cameraX, _cameraY, new CollisionRectangle(0, 0, 400, 4000)));
	_borders.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/colRect.png", 0, 3600, 4000, 400, _cameraX, _cameraY, new CollisionRectangle(0, 0, 4000, 400)));

	//set the current zone

	UpdateZone();

	_currentFrameWater = 0;
	_currentFramePokemon = 0;

	_reflect = false;

	_row = 0;
	_speed = 300;
}

void Enviroment::LoadEnivroment()
{
	std::ifstream readFile;
	const std::string layOutFileName = "Resources/Environment/EnvironmentLayout.xml";
	readFile.open(layOutFileName);

	std::string fileString;

	bool fileRead = false;

	getline(readFile, fileString);

	if (fileString == "<Environment>")
	{
		while (!fileRead)
		{
			getline(readFile, fileString);
			if (fileString == "</Environment>")
			{
				fileRead = true;
			}
			else if (fileString == "<Name>")
			{
				getline(readFile, fileString);
				_displayName = fileString;
			}
			else if (fileString == "<Dimensions>")
			{
				getline(readFile, fileString);
				while (fileString != "</Dimensions>")
				{
					std::stringstream lineStream(fileString);
					std::string dim;
					int i = 0;
					while (getline(lineStream, dim, ','))
					{
						_dimensions[i] = stoi(dim);
						++i;
					}
					getline(readFile, fileString);
				}
				for (int i = 0; i < _dimensions[0]; i++)
				{
					for (int j = 0; j < _dimensions[1]; j++)
					{
						_background.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/Environment/grass" + std::to_string(i) + std::to_string(j) + ".png", 2000 * i, 2000 * j, 2000, 2000, _cameraX, _cameraY, nullptr));
					}
				}
			}
			else if (fileString == "<Trees>")
			{
				getline(readFile, fileString);
				while (fileString != "</Trees>")
				{
					std::stringstream lineStream(fileString);
					std::string cor;
					int xyCor[2];
					int i = 0;
					while (getline(lineStream, cor, ','))
					{
						xyCor[i] = stoi(cor);
						i++;
					}
					_trees.push_back(new Tree(_sdlSetup, _cameraX, _cameraY, xyCor[0], xyCor[1]));
					getline(readFile, fileString);
				}
			}
			else if (fileString == "<WaterTiles>")
			{
				getline(readFile, fileString);
				while (fileString != "</WaterTiles>")
				{
					std::stringstream lineStream(fileString);
					std::string cor;
					int tileData[4];
					int i = 0;
					while (getline(lineStream, cor, ','))
					{
						tileData[i] = stoi(cor);
						i++;
					}
					for (int a = 0; a < tileData[2]; a++)
					{
						for (int b = 0; b < tileData[3]; b++)
						{
							_waterTiles.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/Environment/waterTiles.bmp", tileData[0] + 96 * a, tileData[1] + 128 * b, 96, 128, _cameraX, _cameraY, new CollisionRectangle(0, 0, 96, 128)));
						}
					}
					getline(readFile, fileString);
				}
			}
			else if (fileString == "<GrassTiles>")
			{
				getline(readFile, fileString);
				while (fileString != "</GrassTiles>")
				{
					std::stringstream lineStream(fileString);
					std::string cor;
					int tileData[4];
					int i = 0;
					while (getline(lineStream, cor, ','))
					{
						tileData[i] = stoi(cor);
						i++;
					}
					for (int a = 0; a < tileData[2]; a++)
					{
						for (int b = 0; b < tileData[3]; b++)
						{
							_grassTiles.push_back(new Sprite(_sdlSetup->GetRenderer(), "Resources/Environment/grassTile.png", tileData[0] + 32 * a, tileData[1] + 32 * b, 32, 32, _cameraX, _cameraY, new CollisionRectangle(0, 0, 32, 32)));
						}
					}
					getline(readFile, fileString);
				}
			}
			else if (fileString == "<Buildings>")
			{
				getline(readFile, fileString);
				while (fileString != "</Buildings>")
				{
					std::stringstream lineStream(fileString);
					std::string data[5];
					int i = 0;
					while (getline(lineStream, data[i], ','))
					{
						i++;
					}
					_buildings.push_back(new Building(_sdlSetup, data[0], _cameraX, _cameraY, stoi(data[1]), stoi(data[2]), stoi(data[3]), stoi(data[4])));
					getline(readFile, fileString);
				}
			}
		}
	}
	else
	{
		std::cout << "Invalid file format\n";
	}
	legendary_pokemon = new Sprite(_sdlSetup->GetRenderer(), "Resources/ReshiramAndZekrom.png", 2865, 400, 128, 128, _cameraX, _cameraY, new CollisionRectangle(21, 20, 80, 90));

	readFile.close();

	fileString = "";

	const std::string characterFileName = "Resources/Environment/CharacterLayout.xml";

	readFile.open(characterFileName);

	getline(readFile, fileString);

	fileRead = false;

	while (!fileRead)
	{
		if (fileString == "<Trainers>")
		{
			getline(readFile, fileString);
		}
		else if (fileString == "</Trainers>")
		{
			fileRead = true;
		}
		else if (fileString == "<Trainer>")
		{
			getline(readFile, fileString);
			std::stringstream lineStream(fileString);
			std::string data[6];
			int i = 0;
			while (getline(lineStream, data[i], ','))
			{
				++i;
			}
			getline(readFile, fileString);
			std::array<PokemonGen*, 6> pokemon_set = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
			while (fileString != "</Trainer>")
			{
				if (fileString == "<PokemonSet>")
				{
					int pokemon_index = 0;
					while (fileString != "</PokemonSet>")
					{
						getline(readFile, fileString);
						if (fileString == "<Pokemon>")
						{
							getline(readFile, fileString);
							std::stringstream lineStream2(fileString);
							std::string data2[9];
							int j = 0;
							while (getline(lineStream2, data2[j], ','))
							{
								++j;
							}
							getline(readFile, fileString);
							while (fileString != "</Pokemon>")
							{
								if (fileString == "<MoveSet>")
								{
									int move_index = 0;
									std::array<PokemonMove*, 4> moves = { nullptr, nullptr, nullptr, nullptr };
									while (fileString != "</MoveSet>")
									{
										getline(readFile, fileString);
										if (fileString == "<Move>")
										{
											while (fileString != "</Move>")
											{
												getline(readFile, fileString);
												std::string move_data[3];
												std::stringstream lineStream_2(fileString);
												int k = 0;
												while (getline(lineStream_2, move_data[k], ','))
												{
													++k;
												}
												moves[move_index] = move_list[stoi(move_data[0])];
												++move_index;
												getline(readFile, fileString);
											}
										}
									}
									MoveSet * moveSet = new MoveSet(moves);
									pokemon_set[pokemon_index] = new PokemonGen(pokemon_list[stoi(data2[0])], stoi(data2[1]), stoi(data2[2]), static_cast<StatusEffect>(stoi(data2[3])), stoi(data2[4]), static_cast<PokemonNature>(stoi(data2[5])), ConvertToArray(data2[6]), ConvertToArray(data2[7]), *moveSet);
									++pokemon_index;
									delete moveSet;
								}
								getline(readFile, fileString);
							}
						}
					}
				}
				getline(readFile, fileString);
			}
			_trainers.push_back(new Trainer(data[0], data[1], _sdlSetup, _cameraX, _cameraY, stoi(data[2]), stoi(data[3]), pokemon_set, stoi(data[4]), static_cast<bool>(stoi(data[5]))));
			getline(readFile, fileString);
		}
	}
	readFile.close();

	fileString = "";

	const std::string itemFileName = "Resources/Environment/ItemLayout.txt";

	readFile.open(itemFileName);

	getline(readFile, fileString);

	fileRead = false;
	while (!fileRead)
	{
		if (fileString == "<Items>")
		{
			while (fileString != "</Items>")
			{
				std::string data[4];
				if (fileString == "<Item>")
				{
					while (fileString != "</Item>")
					{
						getline(readFile, fileString);
						std::stringstream lineStream(fileString);
						int i = 0;
						while (getline(lineStream, data[i], ','))
						{
							++i;
						}
						_itemPickups.push_back(new ItemPickup(_sdlSetup, item_list[stoi(data[2])], stoi(data[0]), stoi(data[1]), _cameraX, _cameraY));
						getline(readFile, fileString);
					}
				}
				getline(readFile, fileString);
			}
			fileRead = true;
		}
	}
	readFile.close();
}

void Enviroment::SaveEnviroment()
{
	std::string fileData = "<Trainers>";
	fileData += '\n';
	for (Trainer* trainer : _trainers)
	{
		fileData += "<Trainer>";
		fileData += '\n';
		fileData += trainer->GetClass() + ',' + trainer->GetName() + ',' + std::
			to_string(trainer->GetSprite()->GetImage()->GetX()) + ',' + std::to_string(trainer->GetSprite()->GetImage()->GetY())
			+ ',' + std::to_string(trainer->PrizeMoney()) + ',' + std::to_string(static_cast<int>(trainer->IsDefeated()));
		fileData += '\n';
		fileData += "<PokemonSet>";
		fileData += '\n';
		for (auto oppPokemon : trainer->PokemonSet())
		{
			if (oppPokemon != nullptr)
			{
				fileData += oppPokemon->ToString() + '\n';
			}
		}
		fileData += "</PokemonSet>";
		fileData += '\n';
		fileData += "</Trainer>";
		fileData += '\n';
	}
	fileData += "</Trainers>";

	std::ofstream writeFile;
	const std::string characterFileName = "Resources/Environment/CharacterLayout.xml";
	writeFile.open(characterFileName);
	writeFile << fileData;
	writeFile.close();

	fileData = "";
	fileData = "<Items>";
	fileData += '\n';

	for (ItemPickup* itemPickup : _itemPickups)
	{
		fileData += "<Item>";
		fileData += '\n';
		fileData += std::to_string(itemPickup->GetItemSprite()->GetX()) + ',' + std::
			to_string(itemPickup->GetItemSprite()->GetY()) + ',' + itemPickup->GetItem()->ItemIndex();
		fileData += '\n';
		fileData += "</Item>";
		fileData += '\n';
	}
	fileData += "</Items>";
	fileData += '\n';

	const std::string itemFileName = "Resources/Environment/ItemLayout.txt";
	writeFile.open(itemFileName);
	writeFile << fileData;
	writeFile.close();
}


Enviroment::~Enviroment()
{
	//clear to enivronment objects 
	for (auto element : _background)
	{
		delete element;
	}
	for (auto element : _waterTiles)
	{
		delete element;
	}
	for (auto element : _trees)
	{
		delete element;
	}
	for (auto element : _buildings)
	{
		delete element;
	}
	for (auto border : _borders)
	{
		delete border;
	}
	for (Zone* zone : _zones)
	{
		delete zone;
	}
	delete legendary_pokemon;
	_trees.clear();
}

void Enviroment::DrawBack()
{
	//draw element that will appear behind the player
	for (Sprite* element : _background)
	{
		element->Draw();
	}
	for (Sprite* element : _grassTiles)
	{
		element->Draw();
	}
	for (std::vector<Tree*>::iterator i = _trees.begin(); i != _trees.end(); ++i)
	{
		(*i)->DrawTrunk();
	}
	for (Sprite* element : _waterTiles)
	{
		element->Draw();
	}
	for (Building* element : _buildings)
	{
		element->DrawBack();
	}
	
	for (Trainer* trainer : _trainers)
	{
		trainer->GetSprite()->DrawChar();
	}
	for (ItemPickup* pickup : _itemPickups)
	{
		pickup->Draw();
	}
	if (legendary_pokemon != nullptr)
	{
		legendary_pokemon->Draw();
	}
	for (auto border : _borders)
	{
		border->Draw();
	}
}

void Enviroment::DrawFront()
{
	//draw element that will appear a the player
	for (std::vector<Tree*>::iterator i = _trees.begin(); i != _trees.end(); ++i)
	{
		(*i)->DrawCrown();
	}
	for (auto element : _buildings)
	{
		element->DrawFront();
	}
	for (auto element : _zones)
	{
		element->ZoneSprite()->Draw();
	}
}


std::vector<Sprite*> Enviroment::GetGrass() const
{
	return _grassTiles;
}

std::vector<ItemPickup*>& Enviroment::GetItems()
{
	return _itemPickups;
}

Sprite* Enviroment::GetPokemonCenter()
{
	for (Building* element : _buildings)
	{
		if (element->GetName() == "pokemonCentre")
		{
			return element->GetFront();
		}
	}
	return nullptr;
}


void Enviroment::PokemonActive()
{
	if (legendary_pokemon != nullptr)
	{
		_speed = 50;
		_row = 1;
		_maxLimit = 2;
		_currentFramePokemon = 2;
		_reflect = false;
	}

}

void Enviroment::UpdateZone()
{
	_currentZone = _noZone;
	for (auto zone : _zones)
	{
		if (-*_cameraX + 370 >= zone->ZoneSprite()->GetX() && -*_cameraX + 370 <= zone->ZoneSprite()->GetX() + zone->ZoneSprite()->GetW())
		{
			if (-*_cameraY + 370 >= zone->ZoneSprite()->GetY() && -*_cameraY + 370 <= zone->ZoneSprite()->GetY() + zone->ZoneSprite()->GetH())
			{
				_currentZone = zone;
				break;
			}
		}
	}
}

void Enviroment::Update()
{
	UpdateZone();
	if (legendary_pokemon != nullptr)
	{
		PlayPokemonAnimation();
	}

	PlayAnimation(500);
}


void Enviroment::PlayAnimation(const double speed)
{
	if (_animationDelay + speed < SDL_GetTicks())
	{
		if (_currentFrameWater == 3)
		{
			_currentFrameWater = 0;
		}
		else
		{
			_currentFrameWater++;
		}
		for (auto element : _waterTiles)
		{
			element->GetCrop()->x = _currentFrameWater * 96;
			element->GetCrop()->y = 0;
			element->GetCrop()->w = 96;
			element->GetCrop()->h = 128;
		}
		_animationDelay = SDL_GetTicks();
	}

}

void Enviroment::PlayPokemonAnimation()
{
	if (_animationDelayB + _speed < static_cast<signed>(SDL_GetTicks()))
	{
		legendary_pokemon->GetCrop()->x = (_currentFramePokemon * 64) + 3;
		legendary_pokemon->GetCrop()->y = _row * 61;
		legendary_pokemon->GetCrop()->w = 64;
		legendary_pokemon->GetCrop()->h = 61;
		if (!_reflect)
		{
			_currentFramePokemon++;
		}
		else
		{
			_currentFramePokemon--;
		}
		if (_currentFramePokemon == _maxLimit || _currentFramePokemon == 3)
		{
			_reflect = !_reflect;
		}
		_animationDelayB = SDL_GetTicks();
	}
}

std::vector<CollisionRectangle*> Enviroment::GetCollisionRects()
{
	std::vector<CollisionRectangle*> colRects;
	for (auto element : _trees)
	{
		colRects.push_back(element->get_crown()->GetCollisionRectangle());
	}
	for (auto elements : _buildings)
	{
		colRects.push_back(elements->GetFront()->GetCollisionRectangle());
	}
	for (auto elements : _trainers)
	{
		colRects.push_back(elements->GetSprite()->GetImage()->GetCollisionRectangle());
	}
	for (auto item : _itemPickups)
	{
		colRects.push_back(item->GetItemSprite()->GetCollisionRectangle());
	}
	for (auto border : _borders)
	{
		colRects.push_back(border->GetCollisionRectangle());
	}
	for (auto  waterTile : _waterTiles)
	{
		colRects.push_back(waterTile->GetCollisionRectangle());
	}
	if (legendary_pokemon != nullptr)
	{
		colRects.push_back(legendary_pokemon->GetCollisionRectangle());
	}
	return colRects;
}

std::vector<Trainer*> Enviroment::GetTrainers() const
{
	return _trainers;
}

std::string Enviroment::DisplayName() const
{
	return _currentZone->Name();
}
