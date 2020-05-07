#pragma once
#include "PlayerSprite.h"
#include "Bag.h"

class Player
{
public:
	Player(const std::string name, SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, const std::string file_name, const std::array<PokemonGen*, 6> pokemon_set, Bag* player_bag, int money, Enviroment* init_enviroment);

	//getters and setters

	PlayerSprite* GetPlayerSprite() const;
	std::string GetName() const;
	int GetMoney() const;
	void IncreaseMoney(int amount);
	void DecreaseMoney(int amount);
	std::array<PokemonGen*, 6>& PokemonSet();
	Bag& PlayerBag() const;

	~Player();

private:
	std::string _name;
	std::array<PokemonGen*, 6> _pokemonSet;
	Bag* _playerBag;
	PlayerSprite* _playerImage;
	int _money;
};

