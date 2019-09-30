#pragma once
#include "pch.h"
enum Cell { unoccupied, beaten, occupied };

class CurrentField
{
	
public:
	Cell ** field;
	int depth;

	CurrentField(CurrentField* c)
	{
		depth = c->depth + 1;
		field = new Cell*[8];
		for (size_t i = 0; i < 8; i++)
		{
			field[i] = new Cell[8];
			for (size_t i1 = 0; i1 < 8; i1++)
			{
				field[i][i1] = c->field[i][i1];
			}
		}
	}

	CurrentField()
	{
		depth = -1;
		field = new Cell*[8];
		for (size_t i = 0; i < 8; i++)
		{
			field[i] = new Cell[8];
			for (size_t i1 = 0; i1 < 8; i1++)
			{
				field[i][i1] = unoccupied;
			}
		}
	}

	std::vector<int>* get_unoccupied_cells(int depth);
	void place_queen(int y);

	~CurrentField()
	{

	}

private:

};


