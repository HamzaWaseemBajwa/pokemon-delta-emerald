#include "MainClass.h"
#include <sstream>
#include <fstream>
#include "PokemonMove.h"
#include <ctime>
#include <vector>
#include "HealHealthItem.h"
#include "StatusHealItem.h"
#include "HybridHealItem.h"
#include "Pokeball.h"
#undef main

std::vector<PokemonBase> pokemon_list;
std::vector<PokemonMove*> move_list;
std::vector <Item*> item_list;


void ReadPokemonFromFile()
{
	std::ifstream fin;
	std::string line;
	fin.open("GameData/Pokemon.csv");
	while (getline(fin, line))
	{
		std::stringstream lineStream(line);
		std::array<std::string, 10> data;
		int i = 0;
		while (getline(lineStream, data[i], ','))
		{
			i++;
			if (i == 10)
			{
				i = 9;
			}
		}
		pokemon_list.push_back(PokemonBase{ data });
	}
	fin.close();
}


void ReadMovesFromFile()
{

	std::ifstream fin;
	std::string line;
	fin.open("GameData/Moves.csv");
	int index = 0;
	while (getline(fin, line))
	{
		std::stringstream lineStream(line);
		std::array<std::string, 10> data;
		data[0] = std::to_string(index);
		int i = 1;
		while (getline(lineStream, data[i], ','))
		{
			i++;
		}
		move_list.push_back(new PokemonMove{ data });
		++index;
	}
	fin.close();
}

void ReadItemsFromFile()
{

	std::ifstream fin;
	std::string line;
	fin.open("GameData/Items.csv");
	int index = 0;
	while (getline(fin, line))
	{
		std::stringstream lineStream(line);
		std::array<std::string, 6> data;
		int i = 0;
		while (getline(lineStream, data[i], ','))
		{
			i++;
		}
		if (data[0] == "Heal")
		{
			if (data[4] == "0")
			{
				item_list.push_back(new HealHealthItem(std::to_string(index), data[1], data[2], stoi(data[3])));
			}
			else
			{
				item_list.push_back(new HealHealthItem(std::to_string(index), data[1], data[2], stoi(data[3]), stoi(data[4])));
			}

		}
		else if (data[0] == "Status")
		{
			if (data[4] == "0")
			{
				item_list.push_back(new StatusHealItem(std::to_string(index), data[1], data[2], stoi(data[3])));
			}
			else
			{
				item_list.push_back(new StatusHealItem(std::to_string(index), data[1], data[2], stoi(data[3]), static_cast<StatusEffect>(stoi(data[4]))));
			}

		}
		else if (data[0] == "Hybrid")
		{
			if (data[4] == "0")
			{
				item_list.push_back(new HybridHealItem(std::to_string(index), data[1], data[2], stoi(data[3]), false));
			}
			else
			{
				item_list.push_back(new HybridHealItem(std::to_string(index), data[1], data[2], stoi(data[3]), true));
			}

		}
		else if (data[0] == "Pokeball")
		{
			item_list.push_back(new Pokeball(std::to_string(index), data[1], data[2], stoi(data[3]), stod(data[4])));

		}
		++index;
	}
	fin.close();
}



int main()
{
	ReadPokemonFromFile();
	ReadMovesFromFile();
	ReadItemsFromFile();

	srand(static_cast<unsigned>(time(nullptr)));
	MainClass* cMain = new MainClass();
	cMain->TitleScreen();
	cMain->StartScreen();
	cMain->GameLoop();
	delete cMain;
	return 0;
}
