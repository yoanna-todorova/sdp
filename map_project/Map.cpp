#include "pch.h"
#include "Map.h"

int a = -1;

int enumerate()
{
	a += 1;
	return a;
}


Junction::Junction()
{
	this->in_deg = 0;
	this->out_deg = 0;
	this->index = 0;
	this->name = ' ';
}

void Junction::copy(const Junction & other)
{
	this->in_deg = other.in_deg;
	this->out_deg = other.out_deg;
	this->index = other.index;
	this->name = other.name;
	this->neighbours = other.neighbours;
}

Junction::Junction(const Junction & other)
{
	copy(other);
}

Junction::Junction(std::string str)
{
	in_deg = 0;
	out_deg = 0;
	name = str;
	index = enumerate();
	neighbours = {};
}

Junction & Junction::operator=(const Junction & other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

Street::Street(int distance_, Junction* destination_) :distance(distance_), destination(destination_) {};


Street & Street::operator=(const Street & other)
{
	if (this != &other)
	{
		this->destination->index = other.destination->index;
		this->destination->name = other.destination->name;
		this->destination->neighbours = other.destination->neighbours;
		this->distance = other.distance;
	}

	return *this;
}
;

Map::Map(const Map &other)
{
	std::vector<Junction> map(other.adj);
}

std::vector<Junction> Map::getAdj()
{
	return adj;
}

Map::Map() {};

void Map::addJunction(Junction* junc)
{
	bool alreadyIn = false;
	for (int i = 0; i < adj.size(); i++)
	{
		if (junc->name.compare(adj[i].name)==0) alreadyIn = true;
	}
	if (!alreadyIn) adj.push_back(*junc);
}

void Map::addStreet (Junction* start, Junction* end, int length)
{
	bool existingStreet = false;
	for (int i = 0; i < start->neighbours.size(); i++)
	{
		if (start->neighbours[i].destination == end)
		{
			existingStreet = true;
		}
	}


	for (int i = 0; i < adj.size(); i++)
	{
		if (start->index == adj[i].index)
		{
			for (int j = 0; j < adj.size(); j++)
			{
				if (end->index == adj[j].index && existingStreet==false)
				{
					start->neighbours.push_back({ length,end });
					start->out_deg++;
					end->in_deg++;
					adj[start->index].neighbours.push_back({ length,end });
					adj[start->index].out_deg++;
					adj[end->index].in_deg++;

				}
			}
		}
	}
}
void Map::printMap()
{
	for (int i = 0; i < adj.size(); i++)
	{
		std::cout << adj[i].name << " is connected to: " <<std::endl;
		for (int j = 0; j < adj[i].neighbours.size(); j++)
		{
			std::cout << adj[i].neighbours[j].destination->name;
		
			std::cout << "|| distance between them " << adj[i].neighbours[j].distance << " meters" << std::endl;
		}
		std::cout << std::endl;
	}
}
bool Map::hasPath(Junction* start, Junction* end)
{
	if (start == end) return true;

	bool* visited = new bool[adj.size()];
	for (int i = 0; i < adj.size(); i++)
	{
		visited[i] = false;
	}

	std::list<Junction*>queue;

	visited[start->index] = true;
	queue.push_back(start);

	std::vector<Street>::iterator it;

	while (!queue.empty())
	{
		start = queue.front();
		queue.pop_front();

		for (it = adj[start->index].neighbours.begin(); it != adj[start->index].neighbours.end(); it++)
		{
			if (it->destination->index == end->index) return true;

			if (!visited[it->destination->index])
			{
				visited[it->destination->index] = true;
				queue.push_back(it->destination);
			}
		}
	}

	return false;
}
void Map::findAllBlindAlleys()
{
	std::vector<std::pair<Junction*,Junction*>> blindAlleys;

	for (int i=0; i<adj.size(); i++)
	{
		for (int j = 0; j < adj[i].neighbours.size(); j++)
		{
			if (adj[i].neighbours[j].destination->neighbours.size() == 0)
			{
				std::pair<Junction*, Junction*>new_pair;
				new_pair.first = &adj[i];
				new_pair.second = adj[i].neighbours[j].destination;
				blindAlleys.push_back(new_pair);
			}
		}
	}
	for (int i = 0; i < blindAlleys.size(); i++)
	{
		std::cout << blindAlleys[i].first->name << " -> " << blindAlleys[i].second->name << " X " << std::endl;
	}
}
bool Map::canReachAnywhere(Junction * start)
{
	bool* visited = new bool[adj.size()];
	for (int i = 0; i < adj.size(); i++)
	{
		visited[i] = false;
	}
	visited[start->index] = true;

	for (int i=0; i<adj.size(); i++)
	{
		if (hasPath(start, &adj[i])) visited[i] = true;
	}

	for (int i = 0; i < adj.size(); i++)
	{
		if (visited[i] == false) return false;
	}
	return true;
}
bool Map::canMakeCircuit(Junction * start)
{
	Junction* temp = new Junction(*start);

	bool* visited = new bool[adj.size()];
	for (int i = 0; i < adj.size(); i++)
	{
		visited[i] = false;
	}

	std::list<Junction*>queue;

	queue.push_back(temp);

	std::vector<Street>::iterator it;

	while (!queue.empty())
	{
		temp = queue.front();
		queue.pop_front();

		for (it = adj[temp->index].neighbours.begin(); it != adj[temp->index].neighbours.end(); it++)
		{
			if (it->destination->index == start->index) return true;

			if (!visited[it->destination->index])
			{
				visited[it->destination->index] = true;
				queue.push_back(it->destination);
			}
		}
	}

	return false;
}\

void Map::makeTouristCircuit()
{
	std::vector<Junction> temp(adj);

	if (!isEulerianCycle())
	{
		std::cout << "I am sorry, but such a circuit is not possible!";
	}
	else
	{
		int *edge_count= new int [adj.size()];
		for (int i = 0; i < adj.size(); i++)
		{
			edge_count[i] =adj[i].neighbours.size();
		}
		std::stack<Junction*> curr_path;
		std::vector<Junction*> final_circuit;

		Junction* start =&temp[0];
		curr_path.push(start);

		while (!curr_path.empty())
		{
			if (edge_count[start->index] > 0)
			{
				curr_path.push(start);
				Junction* next = start->neighbours.back().destination;

				edge_count[start->index]--;
				start->neighbours.pop_back();

				start = next;
			}

			else
			{
				final_circuit.push_back(start);
				start = curr_path.top();
				curr_path.pop();
			}

		}

		for (int i = final_circuit.size() - 1; i >= 0; i--)
		{
			std::cout << final_circuit[i]->name;
			if (i)
				std::cout << " -> ";
		}
	}

}

bool Map::isStronglyConnected()
{
	bool* visited = new bool[adj.size()];

	for (int i = 0; i < adj.size(); i++)
	{
		visited[i] = false;
	}

	for (int i = 0; i < adj.size(); i++)
	{
		if (canReachAnywhere(&adj[i])) visited[i] = true;
	}

	for (int i = 0; i < adj.size(); i++)
	{
		if (visited[i] == false) return false;
	}

	return true;
}

bool Map::isEulerianCycle()
{
	if (isStronglyConnected() == false) return false;

	for (int i = 0; i < adj.size(); i++)
	{
		if (adj[i].in_deg != adj[i].out_deg) return false;
	}

	return true;
}

std::vector<std::vector<Junction*>> Map::allPathsBetween(Junction *start, Junction *end)
{

	bool *visited = new bool[adj.size()];
	for (int i = 0; i < adj.size(); i++)
	{
		visited[i] = false;
	}

	std::vector < std::vector<Junction*>> all_paths;
	std::vector<Junction*> curr_path;

	return helper(start, end, visited, curr_path, all_paths);
}

std::vector<std::vector<Junction*>> Map::helper(Junction *start, Junction *end, bool* visited, std::vector<Junction*>curr_path, std::vector<std::vector<Junction*>>&all_paths)
{
	visited[start->index] = true;
	curr_path.push_back(start);

	if (!curr_path.empty())
	{
		if (start == end)
		{
			all_paths.push_back(curr_path);
		}
		else
		{
			std::vector<Street>::iterator i;
			for (i = start->neighbours.begin(); i != start->neighbours.end(); i++)
			{
				if (visited[i->destination->index] == false)
				{
					helper(i->destination, end, visited, curr_path, all_paths);
				}
			}
		}
		visited[start->index] = false;
		curr_path.pop_back();
	}

	return all_paths;
}

void Map::printAllPathsBetween(Junction *start, Junction *end)
{
	std::vector<std::vector<Junction*>> paths = allPathsBetween(start, end);
	for (int i = 0; i < paths.size(); i++)
	{
		std::vector<Junction*> path = paths[i];
		for (int j = 0; j < path.size(); j++)
		{
			if (j < path.size() - 1)
			{
				std::cout << path[j]->name << "->";
			}
			else
			{
				std::cout << path[j]->name;
			}
		}
		std::cout << " " << std::endl;
	}
}

int Map::pathLength(std::vector<Junction*> path)
{
	int distance = 0;

	for (int i = 0; i < path.size(); i++)
	{
		std::vector<Street>::iterator it;
		for (it = path[i]->neighbours.begin(); it != path[i]->neighbours.end(); it++)
		{
			if (i < path.size() - 1)
			{
				if (path[i + 1] == it->destination)
				{
					distance += it->distance;
				}
			}
		}
	}
	return distance;
}

void Map::ThreeShortestPath(Junction*start,Junction*end)
{
	std::vector<std::vector<Junction*>> all_paths = allPathsBetween(start,end);
	std::vector<int>distances;
	for (int i = 0; i < all_paths.size(); i++)
	{
		distances.push_back(pathLength(all_paths[i]));
	}
	std::vector<std::pair<int,std::vector<Junction*>>> path_distance;
	for (int i = 0; i < all_paths.size(); i++)
	{
		std::pair <int, std::vector<Junction*>> temp = std::make_pair(distances[i], all_paths[i]);
		path_distance.push_back(temp);
	}

	std::sort(path_distance.begin(), path_distance.end());

	std::vector<std::vector<Junction*>> final_three;
	{
		for (int i = 0; i < 3; i++)
		{
			final_three.push_back(path_distance[i].second);
		}
	}
	for (int i = 0; i < final_three.size(); i++)
	{
		std::vector<Junction*> path = final_three[i];
		for (int j = 0; j < path.size(); j++)
		{
			if (j < path.size() - 1)
			{
				std::cout << path[j]->name << "->";
			}
			else
			{
				std::cout << path[j]->name;
			}
		}
		std::cout << " " << std::endl;
	}
}

std::vector<std::vector<Junction*>> Map::allAlternativePaths(Junction *start, Junction *end,std::list<Junction*>closed)
{
	bool *visited = new bool[adj.size()];
	for (int i = 0; i < adj.size(); i++)
	{
		visited[i] = false;
	}

	std::vector < std::vector<Junction*>> all_paths;
	std::vector<Junction*> curr_path;

	return alternativePathsUtil(start, end, visited, curr_path, all_paths,closed);
}

std::vector<std::vector<Junction*>> Map::alternativePathsUtil(Junction *start, Junction *end, bool *visited, std::vector<Junction*>curr_path, std::vector<std::vector<Junction*>>&all_paths, std::list<Junction*>closed)
{
	visited[start->index] = true;
	curr_path.push_back(start);

	if (!curr_path.empty())
	{
		if (start == end)
		{
			bool flag = false;
			for (int i = 0; i < curr_path.size(); i++)
			{
				std::list<Junction*>::iterator it;
				for (it=closed.begin(); it!= closed.end(); it++)
				{
					if (curr_path[i] == *it) flag = true;
				}
			}

			if(flag==false) all_paths.push_back(curr_path);
		}
		else
		{
			std::vector<Street>::iterator i;
			for (i = start->neighbours.begin(); i != start->neighbours.end(); i++)
			{
				if (visited[i->destination->index] == false)
				{
					alternativePathsUtil(i->destination, end, visited, curr_path, all_paths,closed);
				}
			}
		}
		visited[start->index] = false;
		curr_path.pop_back();
	}

	return all_paths;
}

void Map::ThreeAlternativeShortestPath(Junction *start, Junction *end, std::list<Junction*> closed)
{
	std::vector<std::vector<Junction*>> all_paths = allAlternativePaths(start, end,closed);
	std::vector<int>distances;
	for (int i = 0; i < all_paths.size(); i++)
	{
		distances.push_back(pathLength(all_paths[i]));
	}
	std::vector<std::pair<int, std::vector<Junction*>>> path_distance;
	for (int i = 0; i < all_paths.size(); i++)
	{
		std::pair <int, std::vector<Junction*>> temp = std::make_pair(distances[i], all_paths[i]);
		path_distance.push_back(temp);
	}

	std::sort(path_distance.begin(), path_distance.end());

	std::vector<std::vector<Junction*>> final_three;
	{
		for (int i = 0; i < 3; i++)
		{
			final_three.push_back(path_distance[i].second);
		}
	}
	for (int i = 0; i < final_three.size(); i++)
	{
		std::vector<Junction*> path = final_three[i];
		for (int j = 0; j < path.size(); j++)
		{
			if (j < path.size() - 1)
			{
				std::cout << path[j]->name << "->";
			}
			else
			{
				std::cout << path[j]->name;
			}
		}
		std::cout << " " << std::endl;
	}
}

void Map::writeOn()
{
	std::string file_name;
	std::cout << "Create a file name: ";
	std::cin >> file_name;
	std::ofstream out_file;
	out_file.open(file_name, std::ios::out);
	for (int i = 0; i <adj.size(); i++)
	{
		out_file <<adj[i].name<< " ";
		for (int j = 0; j < adj[i].neighbours.size(); j++)
		{
			out_file <<adj[i].neighbours[j].destination->name << " " <<adj[i].neighbours[j].distance << " ";
		}
		out_file << std::endl;
	}
	out_file.close();
}

void Map::readFrom(Map & map, std::string file_name)
{
	std::ifstream in_file;
	std::string junction_data;
	in_file.open(file_name, std::ios::in);
	while (!in_file.eof())
	{
		getline(in_file, junction_data);
		extractData(junction_data,map);
	}
	in_file.close();
}

void Map::extractData(std::string& junction_data,Map& map)
{
	std::queue<std::string> string_partition;
	while (!junction_data.empty())
	{
		int counter = 0;
		std::string::iterator it;
		for (it = junction_data.begin(); *it != ' '; it++)
		{
			counter++;
		}
		std::string substr = junction_data.substr(0, counter);
		string_partition.push(substr);
		junction_data = junction_data.erase(0, counter + 1);
	}
	if (!string_partition.empty())
	{
		Junction j(string_partition.front());
		map.addJunction(&j);
		string_partition.pop();

		while (!string_partition.empty())
	    {
			std::string neighbour = string_partition.front();
			Junction *jn=new Junction(neighbour);
			string_partition.pop();
			map.addJunction(jn);
			
			if (!string_partition.empty())
			{
				int length = std::stoi(string_partition.front());
				string_partition.pop();
				map.addStreet(&j, jn, length);
			}
	    }
	}	
}

