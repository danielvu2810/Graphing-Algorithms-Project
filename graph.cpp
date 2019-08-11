#include "graph.h"

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v)
{
	Graph graph;

	graph.set_num_nodes(num_nodes);

	map<int, Node> nodes(graph.get_id_to_node_map());

	//vector<vector<bool>> adjMatrix(num_nodes, vector<bool>(num_nodes, false));

	int num_edges = 0;
	for (int i = 0; i < u.size(); i++)
	{
		if (u[i] != v[i] )
		{
			// undirected so do twice
			//adjMatrix[u[i]][v[i]] = true;
			//adjMatrix[v[i]][u[i]] = true;

			num_edges++;

			graph.add_neigbor(nodes[u[i]], nodes[v[i]]);
			graph.add_neigbor(nodes[v[i]], nodes[u[i]]);
		}
	}

	//graph.setMatrix(adjMatrix);
	graph.set_num_edges(num_edges);

	return graph;
}

Graph::Graph()
{
	num_nodes = 0;
	num_egdes = 0;
}


int Graph::get_num_nodes()
{
	return num_nodes;
}

void Graph::set_num_nodes(int n)
{
	num_nodes = n;

	for (int i = 0; i < n; i++)
	{
		nodes[i] = Node(i);
	}
}

int Graph::get_num_edges()
{
	return num_egdes;
}

void Graph::set_num_edges(int n)
{
	num_egdes = n;
}

map<int, Node> Graph::get_id_to_node_map()
{
	return nodes;
}

//vector<vector<bool>> Graph::getMatrix()
//{
//	return adjMatrix;
//}
//
//void Graph::setMatrix(vector<vector<bool>> matrix)
//{
//	adjMatrix = matrix;
//}

vector<pair<Node, Node>> Graph::get_Edges()
{
	vector<pair<Node, Node>> edges;
	for (int i = 0; i < nodes.size() - 1; i++)
	{
		for (int j = 0; j < nodes[i].neighbors.size(); j++)
		{
			if (i < nodes[i].neighbors[j].id)
				edges.push_back({ nodes[i],nodes[nodes[i].neighbors[j].id] });
		}
	}

	return edges;
}

bool Graph::is_neighbor(Node u, Node v) //O(n)
{
	if (nodes[u.id].neighbors.size() == 0) return false;
	if (nodes[v.id].neighbors.size() == 0) return false;

	if (find(nodes[u.id].neighbors.begin(),nodes[u.id].neighbors.end(),nodes[v.id]) != nodes[u.id].neighbors.end())
		return true;
	return false;
}

vector<Node> Graph::get_neighbors(Node u)
{
	return nodes[u.id].neighbors;
}

void Graph::add_neigbor(Node n, Node v)
{
	nodes[n.id].addneigbor(v);
}

map<Node, int> Graph::get_All_Degrees()
{
	map<Node, int> degrees;

	for (auto &x : nodes)
		degrees[x.second] = x.second.getDegree();

	return degrees;
}


int Graph::get_Distance(Node u, Node v) // O(n^2)
{
	if (is_neighbor(u,v)) return 1;

	vector<int> distance(nodes.size(), 0);

	vector<bool> visited(nodes.size(), false);

	list<Node> queue;

	Node n;

	queue.push_back(u);

	visited[u.id] = true;

	while (!queue.empty())
	{
		n = queue.front();
		queue.pop_front();

		for (auto &x : nodes[n.id].neighbors)
		{
			if (visited[x.id]) continue;

			distance[x.id] = distance[n.id] + 1;
			queue.push_back(x);
			visited[x.id] = true;
		}
	}

	return distance[v.id];
}

vector<Node> Graph::getBFS(Node n) //O(n^2)
{
	vector<Node> bfs;

	vector<bool> visited(nodes.size(), false);

	list<Node> queue;

	visited[n.id] = true;

	queue.push_back(n);

	while (!queue.empty())
	{
		n = queue.front();
		bfs.push_back(n);
		queue.pop_front();

		for (auto &x : nodes[n.id].neighbors)
		{
			if (!visited[x.id])
			{
				visited[x.id] = true;
				queue.push_back(x);
			}

		}
	}

	return bfs;
}


pair<int, Node> Graph::BFS_for_Diameter(Node n) //O(n^2)
{
	int max_distance = 0;
	Node maxnode = n;

	vector<Node> bfs = getBFS(n);

	int distance = get_Distance(n, bfs[bfs.size() - 1]);

	return { distance,bfs[bfs.size() - 1] };
}

int Graph::getNum_2PEdge() //O(n)
{
	int num = 0;

	for (auto &x : nodes)
		num += x.second.getDegree()*(x.second.getDegree() - 1) / 2;

	return num;
}

pair < list<Node>, map < Node, vector<Node>> > Graph::get_Degeneracy()
{

	list<Node> outputList;

	map<Node, int> d = get_All_Degrees();

	map<Node, bool> ht_List;

	map<int, set<Node>> arrayD;

	for (auto &i : d)
	{
		arrayD[i.second].insert(i.first);
		ht_List[i.first] = false;
	}

	map<Node, vector<Node>> N;

	Node v;

	for (auto &x : nodes)
	{
		map<int, set<Node>>::iterator i = arrayD.begin();

		while (i->second.size() == 0 && i != arrayD.end())
			i++;

		if (i == arrayD.end()) break;

		v = *(arrayD[i->first].begin());

		outputList.push_front(v);
		arrayD[i->first].erase(arrayD[i->first].begin());

		if (!ht_List[v])
			ht_List[v] = true;

		vector<Node> neigbors_of_v = get_neighbors(v);

		for (auto &w : neigbors_of_v)
		{
			if (!ht_List[w])
			{
				arrayD[d[w]].erase(arrayD[d[w]].find(w));

				d[w]--;

				arrayD[d[w]].insert(w);

				N[v].push_back(w);
			}
		}
	}

	return { outputList,N };
}

int Graph::get_Triangles()
{
	pair<list<Node>, map<Node, vector<Node>>> degeneracy = get_Degeneracy();

	list<Node> li(degeneracy.first);
	map<Node, vector<Node>> n(degeneracy.second);

	int triangle_Num = 0;
	for (auto &v : li)
	{
		if (n[v].size() >= 2)
		{
			for (int i = 0; i < n[v].size() - 1; i++)
			{
				for (int j = 0; j < n[v].size(); j++)
				{
					if (is_neighbor(n[v][i], n[v][j]))
						triangle_Num++;
				}
			}
		}
	}
	return triangle_Num;
}

Graph:: ~Graph()
{
	num_nodes = 0;
	num_egdes = 0;
	nodes.clear();
}