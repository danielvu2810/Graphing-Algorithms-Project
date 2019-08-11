#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <assert.h>
#include <map>
#include <set>
#include <list>
#include "node.h"
#include "graph.h"

using namespace std;

#ifndef PROJECT3_H_INCLUDED
#define PROJECT3_H_INCLUDED

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v);

int get_NaiveDiameter(Graph graph);
int get_diameter(Graph graph);
float get_clustering_coefficient(Graph graph);
map<int, int> get_degree_distribution(Graph graph);

Graph create_erdos_renyi_graph(int n, float p); 
Graph create_barabasi_albert_graph(int n, int d);


#endif