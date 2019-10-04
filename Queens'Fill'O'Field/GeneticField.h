#pragma once
#pragma once
#include "pch.h"
enum GeneticCell {unc, btn, occ,bno};

class GeneticField
{

public:
	GeneticCell ** field;

	GeneticField(GeneticField* c, int dim)
	{
		field = new GeneticCell*[dim];
		for (size_t i = 0; i < dim; i++)
		{
			field[i] = new GeneticCell[dim];
			for (size_t i1 = 0; i1 < dim; i1++)
			{
				field[i][i1] = c->field[i][i1];
			}
		}
	}

	GeneticField(int dim)
	{
		field = new GeneticCell*[dim];
		for (size_t i = 0; i < dim; i++)
		{
			field[i] = new GeneticCell[dim];
			for (size_t i1 = 0; i1 < dim; i1++)
			{
				field[i][i1] = unc;
			}
		}
	}

	std::vector<int>* get_unoccupied_and_unbeaten_cells(int depth, int dim);
	void place_queen(int x,int y, int dim);
	int get_score(int dim);
	GeneticField* gemmate(int dim);
	GeneticField* crossbreed(GeneticField* parent2, int dim);


	~GeneticField()
	{

	}

private:

};

