#include "pch.h"
#include "CurrentField.h"

std::vector<int>* CurrentField::get_unoccupied_and_unbeaten_cells(int depth,int dim)
{
	std::vector<int>* res = new std::vector<int>();
	for (size_t i = 0; i < dim; i++)
	{
		if (field[std::min(dim-1,depth+1)][i]==unoccupied)
		{
			res->push_back(i);
		}
	}
	return res;
}


bool in_border(int x, int dim)
{
	return 0 <= x && x <= dim-1;
}

void CurrentField::place_queen(int y,int dim)
{
	int z = dim;
	field[depth][y] = occupied;
	for (size_t i = 0; i < dim; i++)
	{
		if (field[depth][i]==unoccupied)
		{
			field[depth][i] = beaten;
		}
		if (field[i][y] == unoccupied)
		{
			field[i][y] = beaten;
		}
		if  (in_border(depth - i,dim)&& in_border(y-i,dim))
		{
			if (field[(depth - i)][(y - i)] == unoccupied)
			{
				field[(depth - i)][(y - i)] = beaten;
			}
		}
		if (in_border(depth - i,dim) && in_border(y + i,dim))
		{
			if (field[(depth - i)][(y + i)] == unoccupied)
			{
				field[(depth - i)][(y + i)] = beaten;
			}
		}
		if (in_border(depth + i,dim) && in_border(y - i,dim))
		{
			if (field[(depth + i)][(y - i)] == unoccupied)
			{
				field[(depth + i)][(y - i)] = beaten;
			}
		}
		if (in_border(depth + i,dim) && in_border(y + i,dim))
		{
			if (field[(depth + i)][(y + i)] == unoccupied)
			{
				field[(depth + i)][(y + i)] = beaten;
			}
		}
		
	}
	
}

