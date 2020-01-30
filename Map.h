#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include<list>
#include <stack>
#include <utility>
#include <queue>
#include <iostream>
#include<fstream>

int enumerate();

struct Junction;


struct Street
{
	int distance;
	Junction* destination;

	Street(int, Junction*);
	Street& operator=(const Street& other);
};

struct Junction
{
	int in_deg;
	int out_deg;
	int index;
	std::string name;
	std::vector<Street> neighbours;

	Junction();
	void copy(const Junction&);
	Junction(const Junction&);
	Junction(std::string);
	Junction &operator=(const Junction& other);
};

class Map
{
	std::vector<Junction> adj;

public:
	Map(const Map&);
	std::vector<Junction> getAdj();
	Map();
	void addJunction(Junction*);
	void addStreet(Junction*, Junction*, int);
	void printMap();
	bool hasPath(Junction*, Junction*);
	void findAllBlindAlleys();
	bool canReachAnywhere(Junction*);
	bool canMakeCircuit(Junction*);
	void makeTouristCircuit();
	bool isStronglyConnected();
	bool isEulerianCycle();
	std::vector<std::vector<Junction*>>helper(Junction *, Junction *, bool*, std::vector<Junction*>, std::vector<std::vector<Junction*>>&);
	std::vector<std::vector<Junction*>>allPathsBetween(Junction *, Junction *);
	void printAllPathsBetween(Junction*, Junction*);
	int pathLength(std::vector <Junction*>);
	void ThreeShortestPath(Junction*, Junction*);
	std::vector<std::vector<Junction*>>allAlternativePaths(Junction *, Junction *,std::list<Junction*>);
	std::vector<std::vector<Junction*>>alternativePathsUtil(Junction *, Junction *, bool*, std::vector<Junction*>, std::vector<std::vector<Junction*>>&, std::list<Junction*>);
	void ThreeAlternativeShortestPath(Junction*, Junction*,std::list<Junction*>);
	void writeOn();
	void readFrom(Map&,std::string file_name);
	void extractData(std::string&,Map&);

};
