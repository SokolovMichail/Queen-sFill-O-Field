#include "pch.h"
#include "CurrentField.h"
#include "GeneticField.h"

void print_output(CurrentField * res,int dim)
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t i1 = 0; i1 < dim; i1++)
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

void print_output(GeneticField* res, int dim)
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t i1 = 0; i1 < dim; i1++)
		{
			if (res->field[i][i1] == occ)
			{
				std::cout << '*';
			}
			else if ((res->field[i][i1] == btn))
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

GeneticField* genetic_algorithm(int dim)
{
	std::priority_queue<std::tuple<GeneticField*, int>, std::vector<std::tuple<GeneticField*, int>>, CustomCompare> specimen;
	std::random_device rd;
	std::mt19937 g(rd());
	for (size_t i = 0; i < 16; i++)
	{
		GeneticField* curr = new GeneticField(dim);
		for (size_t i = 0; i < dim; i++)
		{
			std::vector<int>* rs = curr->get_unoccupied_and_unbeaten_cells(i, dim);
			if (rs->size() == 0)
			{
				delete curr;
				continue;
			}
			std::shuffle(rs->begin(), rs->end(), g);
			curr->place_queen(i, rs->at(0), dim);
			delete rs;
		}
		specimen.push(std::make_tuple(curr, curr->get_score(dim)));
	}

	

}

void solve_genetic()
{
	genetic_algorithm(8);
}

struct CustomCompare
{
	bool operator()(std::tuple<GeneticField*, int> a, std::tuple<GeneticField*, int> b)
	{
		return std::get<1>(a) > std::get<1>(b);
	}

};

CurrentField* dfs(CurrentField* curr,int dim)
{
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(std::time(nullptr));
	//print_output(curr);
	std::vector<int>* rs = curr->get_unoccupied_and_unbeaten_cells(curr->depth,dim);
	if (curr->depth == dim-1)
	{
		return curr;
	}
	else
	{
		std::shuffle(rs->begin(), rs->end(), g);
		for (size_t i = 0; i < rs->size(); i++)
		{
			CurrentField * now_at = new CurrentField(curr,dim);
			now_at->place_queen(rs->at(i),dim);
			CurrentField* c = dfs(now_at,dim);
			if (c != nullptr)
			{
				return c;
			}
		}
	}
	delete rs;
	return nullptr;

}

CurrentField* dfs_primer(int dim)
{
	CurrentField * start = new CurrentField(dim);
	return dfs(start,dim);
}

void solve_dfs()
{
	int dim = 8;
	auto starttime = std::chrono::steady_clock::now();
	CurrentField * res = dfs_primer(dim);
	print_output(res,dim);
	auto endtime = std::chrono::steady_clock::now();
	auto difference = endtime - starttime;
	std::cout << "Time elapsed: "
		<< std::fixed
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() / 1e+9
		<< " seconds"
		<< std::endl;
}

CurrentField * bfs(int dim)
{
	std::queue<CurrentField*> queue_nodes;
	CurrentField * start = new CurrentField(dim);
	std::random_device rd;
	std::mt19937 g(rd());
	g.seed(std::time(nullptr));
	queue_nodes.push(start);
	while (!queue_nodes.empty())
	{
		CurrentField * curr = queue_nodes.front();
		queue_nodes.pop();
		//print_output(curr);
		std::vector<int>* rs = curr->get_unoccupied_and_unbeaten_cells(curr->depth,dim);
		if (curr->depth == dim - 1)
		{
			return curr;
		}
		else
		{
			std::shuffle(rs->begin(), rs->end(), g);
			for (size_t i = 0; i < rs->size(); i++)
			{
				CurrentField * now_at = new CurrentField(curr,dim);
				now_at->place_queen(rs->at(i),dim);
				queue_nodes.push(now_at);
			}
		}
		delete rs;
	}
	std::cout << "WTF";
}


void solve_bfs()
{
	int dim = 8;
	auto starttime = std::chrono::steady_clock::now();
	CurrentField * res = bfs(dim);
	print_output(res,dim);
	auto endtime = std::chrono::steady_clock::now();
	auto difference = endtime - starttime;
	std::cout << "Time elapsed: "
		<< std::fixed
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() / 1e+9
		<< " seconds"
		<< std::endl;
}