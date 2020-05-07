#include "Player.h"

Player::Player(const std::string name, SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, const std::string file_name, const std::array<PokemonGen*, 6> pokemon_set, Bag* player_bag, const int money, Enviroment* init_enviroment) :
	_name(name),
	_pokemonSet(pokemon_set),
	_playerBag(player_bag),
	_playerImage(new PlayerSprite(passed_sdl_setup, p_camera_x, p_camera_y, file_name, init_enviroment)),
	_money(money)
{}

PlayerSprite* Player::GetPlayerSprite() const
{
	return _playerImage;
}

Player::~Player()
{
	delete _playerImage;
}

std::string Player::GetName() const
{
	return _name;
}

int Player::GetMoney() const
{
	return _money;
}

void Player::IncreaseMoney(int amount)
{
	_money += amount;
}

void Player::DecreaseMoney(int amount)
{
	_money -= amount;
}

std::array<PokemonGen*, 6>& Player::PokemonSet()
{
	return _pokemonSet;
}

Bag& Player::PlayerBag() const
{
	return *_playerBag;
}
