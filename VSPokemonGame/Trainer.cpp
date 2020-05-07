#include "Trainer.h"

Trainer::Trainer(const std::string character_class, const std::string name, SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, const int x, const int y, const std::array<PokemonGen*, 6> pokemon_set, const int prize_money, const bool defeated) :
	BaseCharacter(character_class, name, passed_sdl_setup, p_camera_x, p_camera_y, x, y),
	_pokemonSet(pokemon_set),
	_prizeMoney(prize_money),
	_defeated(defeated)
{
	_battleSprite = nullptr;
}

Trainer::~Trainer()
{
}

void Trainer::DeleteBattleSprite()
{
	delete _battleSprite;
	_battleSprite = nullptr;
}

std::array<PokemonGen*, 6>& Trainer::PokemonSet()
{
	return _pokemonSet;
}

int& Trainer::PrizeMoney()
{
	return _prizeMoney;
}

void Trainer::InitializeBattleSprite(SdlSetup* battle_sdl_setup)
{
	_battleSprite = new Sprite(battle_sdl_setup->GetRenderer(), "Resources/CharacterSprites/BattleSprites/" + GetClass() + GetName() + ".png", 200, 20, 120, 120, nullptr, nullptr, nullptr);
}

void Trainer::DrawSprite() const
{
	_battleSprite->DrawSteady();
}

void Trainer::SetDefeated()
{
	_defeated = true;
}

bool Trainer::IsDefeated() const
{
	return _defeated;
}
