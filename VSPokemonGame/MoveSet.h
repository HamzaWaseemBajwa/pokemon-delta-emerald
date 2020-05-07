#pragma once

#include <array>
#include "PokemonMove.h"

class MoveSet //class that stores a Pokemon's current set of moves, minimum of 1 and maximum 4
{
public:

	explicit MoveSet(std::array<PokemonMove*, 4> moves); //ctor, convert from Move Array to MoveSet
	MoveSet(std::array<PokemonMove*, 4> moves, std::array<int, 4> pps); //ctor, use Move Array and Move PP Array to make MoveSet
	std::string ToString(); //convert to file writable string
	void AddMove(PokemonMove* move); //add move to MoveSet
	void DisplayMoves(); //Show moveset on console
	void UseMove(int move_index); //Use the selected Move, reduce PP by 1
	void RestorePp(); //Restore the PPs of all Moves in moveset
	PokemonMove* operator[](const int index); //access move by passed index
	int GetPp(const int index); //get remaining move PP of passed move index

	MoveSet();

private:
	std::array<PokemonMove*, 4> _moveSlots; //Array of Pokemon Moves
	std::array<int, 4> _movePPs; //Array of Remaining Move PPs
};
