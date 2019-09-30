#include "pch.h"
#include "CurrentField.h"

std::vector<int>* CurrentField::get_unoccupied_cells(int depth)
{
	std::vector<int>* res = new std::vector<int>();
	for (size_t i = 0; i < 8; i++)
	{
		if (field[std::min(7,depth+1)][i]==unoccupied)
		{
			res->push_back(i);
		}
	}
	return res;
}

bool in_border(int x)
{
	return 0 <= x && x <= 7;
}

void CurrentField::place_queen(int y)
{
	field[depth][y] = occupied;
	for (size_t i = 0; i < 8; i++)
	{
		if (field[depth][i]==unoccupied)
		{
			field[depth][i] = beaten;
		}
		if (field[i][y] == unoccupied)
		{
			field[i][y] = beaten;
		}
		if  (in_border(depth - i)&& in_border(y-i))
		{
			if (field[(depth - i)][(y - i)] == unoccupied)
			{
				field[(depth - i)][(y - i)] = beaten;
			}
		}
		if (in_border(depth - i) && in_border(y + i))
		{
			if (field[(depth - i)][(y + i)] == unoccupied)
			{
				field[(depth - i)][(y + i)] = beaten;
			}
		}
		if (in_border(depth + i) && in_border(y - i))
		{
			if (field[(depth + i)][(y - i)] == unoccupied)
			{
				field[(depth + i)][(y - i)] = beaten;
			}
		}
		if (in_border(depth + i) && in_border(y + i))
		{
			if (field[(depth + i)][(y + i)] == unoccupied)
			{
				field[(depth + i)][(y + i)] = beaten;
			}
		}
		
	}
	
}

