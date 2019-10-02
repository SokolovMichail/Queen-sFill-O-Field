#pragma once
#include "pch.h"
enum Cell { unoccupied, beaten, occupied };

class CurrentField
{
	
public:
	Cell ** field;
	int depth;

	CurrentField(CurrentField* c,int dim)
	{
		depth = c->depth + 1;
		field = new Cell*[dim];
		for (size_t i = 0; i < dim; i++)
		{
			field[i] = new Cell[dim];
			for (size_t i1 = 0; i1 < dim; i1++)
			{
				field[i][i1] = c->field[i][i1];
			}
		}
	}

	CurrentField(int dim)
	{
		depth = -1;
		field = new Cell*[dim];
		for (size_t i = 0; i < dim; i++)
		{
			field[i] = new Cell[dim];
			for (size_t i1 = 0; i1 < dim; i1++)
			{
				field[i][i1] = unoccupied;
			}
		}
	}

	std::vector<int>* get_unoccupied_and_unbeaten_cells(int depth, int dim);
	void place_queen(int y,int dim);
	

	~CurrentField()
	{

	}

private:

};


