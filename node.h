#include <vector>
#include <iostream>

using namespace std;

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
/*
Node must
	have a default constructor
	have a public member int 'id' which uniquely identifies a node (no two nodes have the same id).
		   id must be set in the constructor and thereafter not modified
	have the following method:
		bool operator==(const Node& other) const {return id == other.id;}

You may add whatever other members you like to Node
*/

class Node  
{
public:
	int id;
	vector<Node> neighbors;

	Node() 
	{ 
	}

	Node(int i) {  id = i;  }
	
	void addneigbor(Node n) { neighbors.push_back(n); }
	int getDegree() { return neighbors.size(); }

	bool operator==(const Node& other) const { return this->id == other.id; }
	bool operator!=(const Node& other) const { return this->id != other.id; }
	bool operator>(const Node& other) const { return this->id > other.id; }
	bool operator>=(const Node& other) const { return this->id >= other.id; }
	bool operator<(const Node& other) const { return this->id < other.id; }
	bool operator<=(const Node& other) const { return this->id <= other.id; }

	friend ostream& operator<<(ostream& os, const Node& other)
	{
		os << other.id;	
		return os;
	}

	~Node() 
	{
	};
};

#endif