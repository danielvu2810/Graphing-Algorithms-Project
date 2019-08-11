#include "node.h"
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class AbstractGraph
{
public:
	virtual int get_num_nodes() = 0;
	virtual int get_num_edges() = 0;
	virtual bool is_neighbor(Node u, Node v) = 0;
	
	virtual std::vector<Node> get_neighbors(Node u) = 0;

	virtual std::map<int, Node> get_id_to_node_map() = 0;
};

class Graph : public AbstractGraph
{
private:
	int num_nodes;
	int num_egdes;
	//vector<vector<bool>> adjMatrix;
	map<int, Node> nodes;

public:
	Graph();

	int get_num_nodes();
	void set_num_nodes(int num_nodes);

	int get_num_edges();
	void set_num_edges(int num_edges);
	map<int, Node> get_id_to_node_map();
	
	//vector<vector<bool>> getMatrix();

	vector<pair<Node, Node>> get_Edges();

	//void setMatrix(vector<vector<bool>> adjMatrix);

	bool is_neighbor(Node u, Node v);
	vector<Node> get_neighbors(Node u);
	void add_neigbor(Node u, Node v);
	map<Node, int> get_All_Degrees();
	int get_Distance(Node u, Node v);

	vector<Node> getBFS(Node n);
	pair<int, Node> BFS_for_Diameter(Node n);

	int getNum_2PEdge();
	pair < list<Node>, map < Node, vector<Node>> > get_Degeneracy();
	int get_Triangles();


	~Graph();
};
#endif