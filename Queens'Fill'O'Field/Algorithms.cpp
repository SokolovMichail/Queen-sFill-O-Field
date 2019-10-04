#include "pch.h"
#include "CurrentField.h"
#include "GeneticField.h"

struct CustomCompare
{
	bool operator()(std::tuple<GeneticField*, int> a, std::tuple<GeneticField*, int> b)
	{
		return std::get<1>(a) > std::get<1>(b);
	}

};

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
	int dim_queue= 40;
	std::priority_queue<std::tuple<GeneticField*, int>,
		std::vector<std::tuple<GeneticField*,
		int>>, CustomCompare>* specimen = new std::priority_queue<std::tuple<GeneticField*, int>,
		std::vector<std::tuple<GeneticField*,
		int>>, CustomCompare>();
	std::random_device rd;
	std::mt19937 g(rd());
	std::mt19937 g1(std::chrono::system_clock::now().time_since_epoch().count());
	srand(time(NULL));
	for (size_t i = 0; i < dim_queue; i++)
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
		specimen->push(std::make_tuple(curr, curr->get_score(dim)));
		//print_output(curr, dim);
	}
	int generation = 0;
	while (true)
	{
		std::cout << "Generation " << generation << std::endl;
		std::cout << "Conflicts in Generation  ";
		generation++;
		std::vector<GeneticField*>* curr_layouts = new std::vector<GeneticField*>();
		for (size_t i = 0; i < dim_queue; i++)
		{
			
			int score = std::get<1>(specimen->top());
			std::cout << score << " ";
			if (score <= 0)
			{
				return std::get<0>(specimen->top());
			}
			curr_layouts->push_back(std::get<0>(specimen->top()));
			specimen->pop();
		}
		std::cout << std::endl;
		for (size_t i = 0; i < dim_queue; i++)
		{
			int parent1 = rand() % dim_queue;
			int parent2 = rand() % dim_queue;
			int prob = rand() % 100;
			if (prob % 10 == 0)
			{
				GeneticField* tmp = curr_layouts->at(parent1)->crossbreed(curr_layouts->at(parent2), dim);
				GeneticField* tmp1 = tmp->gemmate(dim);
				delete tmp;
				tmp = tmp1;
				specimen->push(std::make_tuple(tmp, tmp->get_score(dim)));
				//print_output(tmp, dim);
			}
			else
			{
				GeneticField* tmp = curr_layouts->at(parent1)->crossbreed(curr_layouts->at(parent2), dim);
				specimen->push(std::make_tuple(tmp, tmp->get_score(dim)));
				//print_output(tmp,dim);
			}
			//print_output(tmp, dim);
			
		}
		std::priority_queue<std::tuple<GeneticField*, int>, std::vector<std::tuple<GeneticField*, int>>, CustomCompare>* specimen_new
			= new std::priority_queue<std::tuple<GeneticField*, int>, std::vector<std::tuple<GeneticField*, int>>, CustomCompare>();
		for (size_t i = 0; i < dim; i++)
		{
			specimen->push(std::make_tuple(curr_layouts->at(i),curr_layouts->at(i)->get_score(dim)));
		}
		for (size_t i = 0; i < dim_queue; i++)
		{
			specimen_new->push(specimen->top());
			specimen->pop();
		}
		delete specimen;
		specimen = specimen_new;
		delete curr_layouts;

	}
}




void solve_genetic()
{
	int dim = 8;
	auto starttime = std::chrono::steady_clock::now();
	GeneticField * res = genetic_algorithm(dim);
	print_output(res, dim);
	auto endtime = std::chrono::steady_clock::now();
	auto difference = endtime - starttime;
	std::cout << "Time elapsed: "
		<< std::fixed
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() / 1e+9
		<< " seconds"
		<< std::endl;
}

GeneticField* burnout(int dim)
{
	std::random_device rd;
	std::mt19937 g(rd());
	GeneticField* curr = new GeneticField(dim);
	for (size_t i = 0; i < dim; i++)
	{
		std::vector<int>* rs = curr->get_unoccupied_and_unbeaten_cells(i, dim);
		if (rs->size() == 0)
		{
		}
		std::shuffle(rs->begin(), rs->end(), g);
		curr->place_queen(i, rs->at(0), dim);
		delete rs;
	}
	double temp = 200;
	double fin_temp = 0.00001;
	double alpha = 0.99;
	int counter = 0;
	while ( curr->get_score(dim) != 0 && counter < 400)
	{
		counter++;
		GeneticField* new_one = curr->gemmate(dim);
		int z = new_one->get_score(dim);
		if (z < temp)
		{
			delete curr;
			curr = new_one;
		}
		else
		{
			if (temp >= 0&&exp((temp - z) / temp) > 0.8)
			{
				std::cout << "Here!" << std::endl;
				delete curr;
				curr = new_one;
			}
		}
		temp -= 1;// (temp * alpha / (counter*1.0));
		std::cout << "Current Temperature" << temp << " and Current score is " << curr->get_score(dim) << std::endl;
		
	}
	std::cout << curr->get_score(dim) << std::endl;
	return curr;

}

void solve_burnout()
{
	int dim = 8;
	auto starttime = std::chrono::steady_clock::now();
	GeneticField * res = burnout(dim);
	print_output(res, dim);
	auto endtime = std::chrono::steady_clock::now();
	auto difference = endtime - starttime;
	std::cout << "Time elapsed: "
		<< std::fixed
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(difference).count() / 1e+9
		<< " seconds"
		<< std::endl;
}


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
	int dim =12;
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