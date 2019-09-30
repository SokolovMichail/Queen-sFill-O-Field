#include "pch.h"
#include "CurrentField.h"

void print_output(CurrentField * res)
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t i1 = 0; i1 < 8; i1++)
		{
			if (res->field[i][i1] == occupied)
			{
				std::cout << '*';
			}
			else if ((res->field[i][i1] == beaten))
			{
				std::cout << "!";
			}
			else
			{
				std::cout << '#';
			}

		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

CurrentField* dfs_primer()
{
	CurrentField * start = new CurrentField();
	return dfs(start);
}

CurrentField* dfs(CurrentField* curr)
{
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(std::time(nullptr));
	//print_output(curr);
	std::vector<int>* rs = curr->get_unoccupied_cells(curr->depth);
	if (curr->depth == 7)
	{
		return curr;
	}
	else
	{
		std::shuffle(rs->begin(), rs->end(), g);
		for (size_t i = 0; i < rs->size(); i++)
		{
			CurrentField * now_at = new CurrentField(curr);
			CurrentField* c = dfs(now_at);
			if (c != nullptr)
			{
				return c;
			}
		}
	}
	delete rs;
	return nullptr;

}

void solve_dfs()
{
	auto starttime = std::chrono::steady_clock::now();
	CurrentField * res = dfs_primer();
	print_output(res);
	auto endtime = std::chrono::steady_clock::now();
	auto difference = endtime - starttime;
	std::cout << "Time elapsed: "
		<< std::fixed
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() / 1e+9
		<< " seconds"
		<< std::endl;
}

CurrentField * bfs()
{
	std::queue<CurrentField*> queue_nodes;
	CurrentField * start = new CurrentField();
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(std::time(nullptr));
	queue_nodes.push(start);
	while (!queue_nodes.empty())
	{
		CurrentField * curr = queue_nodes.front();
		queue_nodes.pop();
		//print_output(curr);
		std::vector<int>* rs = curr->get_unoccupied_cells(curr->depth);
		if (curr->depth == 7)
		{
			return curr;
		}
		else
		{
			std::shuffle(rs->begin(), rs->end(), g);
			for (size_t i = 0; i < rs->size(); i++)
			{
				CurrentField * now_at = new CurrentField(curr);
				now_at->place_queen(rs->at(i));
				queue_nodes.push(now_at);
			}
		}
		delete rs;
	}
}


void solve_bfs()
{
	auto starttime = std::chrono::steady_clock::now();
	CurrentField * res = bfs();
	print_output(res);
	auto endtime = std::chrono::steady_clock::now();
	auto difference = endtime - starttime;
	std::cout << "Time elapsed: "
		<< std::fixed
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() / 1e+9
		<< " seconds"
		<< std::endl;
}