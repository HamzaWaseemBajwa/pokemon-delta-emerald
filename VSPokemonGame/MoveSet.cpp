#include "MoveSet.h"
#include <iostream>

MoveSet::MoveSet(std::array<PokemonMove*, 4> moves)
{
	_moveSlots = moves; //assign moves to MoveSlots
	for (int i = 0; i < 4; i++)
	{
		if (moves[i] != nullptr) //if move exists, assign its Base PP to remaining PP array
		{
			_movePPs[i] = moves[i]->BasePp();
		}
	}
}

MoveSet::MoveSet(const std::array<PokemonMove*, 4> moves, const std::array<int, 4> pps)
{
	_moveSlots = moves;
	_movePPs = pps;
}

MoveSet::MoveSet()
{
	for (int i = 0; i < 4; i++)
	{
		_moveSlots[i] = nullptr;
		_movePPs[i] = 0;
	}
}

std::string MoveSet::ToString()
{
	std::string movesetString = "<MoveSet>";
	movesetString += '\n';
	for (int i = 0; i < 4; ++i)
	{
		if (_moveSlots[i] != nullptr)
		{
			movesetString += "<Move>";
			movesetString += '\n' +
				_moveSlots[i]->GetIndex() + ',' + std::to_string(_movePPs[i]) + '\n'
				+ "</Move>" + '\n';
		}
	}
	movesetString += "</MoveSet>";
	return movesetString;
}

void MoveSet::AddMove(PokemonMove* move)
{
	int i = 0;
	while (_moveSlots[i] != nullptr && i < 4) //find empty move slot
	{
		i++;
	}
	if (i != 4) //if slot found
	{
		_moveSlots[i] = move;
		_movePPs[i] = move->BasePp();
	}
	else
	{
		std::cout << "All moveslots full!\n";
	}
}

void MoveSet::DisplayMoves()
{
	for (int i = 0; i < 4; i++) {
		if (_moveSlots[i] != nullptr)
		{
			std::cout << _moveSlots[i]->Name() << " (" << _movePPs[i] << " / " << _moveSlots[i]->BasePp() << ")" << '\n';
		}
		else
		{
			std::cout << "Empty Slot" << '\n';
		}
	}
}

void MoveSet::UseMove(const int move_index)
{
	_movePPs[move_index] -= 1; //reduce PP by 1
}


void MoveSet::RestorePp()
{
	for (int i = 0; i < 4; ++i)
	{
		if (_moveSlots[i] != nullptr)
		{
			_movePPs[i] = _moveSlots[i]->BasePp(); //set remaining PP to base PP
		}
	}
}

PokemonMove* MoveSet::operator[](const int index)
{
	return _moveSlots[index];
}

int MoveSet::GetPp(const int index)
{
	return _movePPs[index];
}
