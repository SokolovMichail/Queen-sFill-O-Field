#include "pch.h"
#include "GeneticField.h"

std::vector<int>* GeneticField::get_unoccupied_and_unbeaten_cells(int col, int dim)
{
	std::vector<int>* res = new std::vector<int>();
	for (size_t i = 0; i < dim; i++)
	{
		if (field[col][i] == unc)
		{
			res->push_back(i);
		}
	}
	return res;
}

void GeneticField::place_queen(int x, int y, int dim)
{
	int z = dim;
	field[x][y] = occ;
	for (size_t i = 0; i < dim; i++)
	{
		if (field[x][i] == unc)
		{
			field[x][i] = btn;
		}
		if (field[i][y] == unc)
		{
			field[i][y] = btn;
		}
	}
}

int GeneticField::get_score(int dim)
{
	int score = 0;
	std::vector<int> x_values;
	std::vector<int> y_values;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t i1= 0; i1 < dim; i1++)
		{
			if (field[i][i1] == occ)
			{
				x_values.push_back(i);
				y_values.push_back(i1);
			}
		}
	}
	for (size_t i = 0; i < x_values.size; i++)
	{
		for (size_t i1 = i; i1 < x_values.size; i1++)
		{
			if (std::abs(x_values[i] - x_values[i1]) == std::abs(y_values[i] - y_values[i1]))
			{
				score += 1;
			}
		}
	}
	return score;
}
