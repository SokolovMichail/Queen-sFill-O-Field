#include "pch.h"
#include "CurrentField.h"


CurrentField * bfs()
{
	std::queue<CurrentField*> queue_nodes;
	CurrentField * start = new CurrentField();
	while (!queue_nodes.empty())
	{
		CurrentField * curr = queue_nodes.front();
		queue_nodes.pop();
		std::vector<int>* rs = curr->get_unoccupied_cells(curr->depth);
		if (curr->depth == 8)
		{
			if (rs->size() != 0)
			{
				curr->place_queen(rs->at(0));
				return curr;
			}
		}
		else
		{
			std::random_shuffle(rs->begin(), rs->end());
			for (size_t i = 0; i < rs->size(); i++)
			{
				curr->place_queen(rs->at(i));
				queue_nodes.push(new CurrentField(curr));
			}
		}
	}

}

void print_output()
{

}

void solve_bfs()
{

}