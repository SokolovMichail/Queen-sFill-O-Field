#include "pch.h"
#include "GeneticField.h"
#include "Algorithms.h"

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
	for (size_t i = 0; i < x_values.size(); i++)
	{
		for (size_t i1 = i+1; i1 < x_values.size(); i1++)
		{
			if (std::abs(x_values[i] - x_values[i1]) == std::abs(y_values[i] - y_values[i1]))
			{
				score += 1;
			}
		}
	}
	return score;
}

GeneticField * GeneticField::gemmate(int dim)
{
	std::vector<int> x_values;
	std::vector<int> y_values;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t i1 = 0; i1 < dim; i1++)
		{
			if (field[i][i1] == occ)
			{
				x_values.push_back(i);
				y_values.push_back(i1);
			}
		}
	}
	int source = rand() % dim;
	int target = rand() % dim;
	GeneticField* res = new GeneticField(this, dim);
	std::swap(res->field[x_values.at(source)][y_values.at(source)],
		res->field[x_values.at(target)][y_values.at(target)]);
	return res;

}

GeneticField* GeneticField::crossbreed(GeneticField* parent2, int dim)
{
	GeneticField * res = new GeneticField(dim);
	int counter = 0;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t i1 = 0; i1 < dim; i1++)
		{
			if (field[i][i1] == occ && parent2->field[i][i1] == occ)
			{
				res->place_queen(i, i1, dim);
				counter++;
			}
		}
	}
	std::random_device rd;
	std::mt19937 g(rd());
	for (size_t i = 0; i < dim; i++)
	{
		std::vector<int>* rs = res->get_unoccupied_and_unbeaten_cells(i,dim);
		if (rs->size() != 0)
		{
			std::shuffle(rs->begin(), rs->end(), g);
			res->place_queen(i, rs->at(0), dim);
		}
		delete rs;
	}
	return res;
}
