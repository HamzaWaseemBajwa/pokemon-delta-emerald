#pragma once
#include "BaseCharacter.h"
#include "PokemonGen.h"

class Trainer : public BaseCharacter
{
public:
	Trainer(const std::string character_class, const std::string name, SdlSetup* passed_sdl_setup, double* p_camera_x, double* p_camera_y, const int x, const int y, const std::array<PokemonGen*, 6> pokemon_set, const int prize_money, bool defeated);

	//getters

	std::array<PokemonGen*, 6>& PokemonSet(); 
	int& PrizeMoney();
	bool IsDefeated() const;

	void InitializeBattleSprite(SdlSetup* battle_sdl_setup);	//set battle sprite
	void DrawSprite() const;	//draw battle sprite
	void SetDefeated();	//set as defeated
	
	virtual ~Trainer();
	void DeleteBattleSprite();

protected:
	std::array<PokemonGen*, 6> _pokemonSet; //the trainer's pokemon set
	int _prizeMoney;	//the trainers prize money
	Sprite* _battleSprite;	//the players battle sprite
	bool _defeated;	//boolean to track if the traine rhas been defeated
};

