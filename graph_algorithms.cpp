#include "project3.h"
#include "graph.h"

int get_NaiveDiameter(Graph graph)
{
	int max_diameter = 0;
	
	map<int,Node> nodes = graph.get_id_to_node_map();

	int size = nodes.size();

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 1; j < size; j++)
		{
			int distance = graph.get_Distance(nodes[i], nodes[j]);
			if (max_diameter < distance) max_diameter = distance;
		}
	}

	return max_diameter;
}

int get_diameter(Graph graph)
{
	int max_diameter = 0;

	int temp = 0;

	map<int, Node> nodes = graph.get_id_to_node_map();

	int size = nodes.size();

	vector<bool> visited(size,false);

	if (size <= 1) return 0;

	if(size > 100)
	{
		mt19937 mt = mt19937(chrono::system_clock::now().time_since_epoch().count());

		uniform_int_distribution<int> ui = uniform_int_distribution<int>(0, size - 1);

		Node randomNode(nodes[ui(mt)]);

		while (1)
		{
			pair<int, Node> diameter = graph.BFS_for_Diameter(randomNode);

			visited[randomNode.id] = true;

			if (max_diameter < diameter.first && !visited[diameter.second.id])
			{
				max_diameter = diameter.first;
				randomNode = diameter.second;
			}
			else break;
		}

		return max_diameter;
	}

	else return get_NaiveDiameter(graph);
}

float get_clustering_coefficient(Graph graph)
{
	float result;

	//get denominator
	int twoPathedge_num = graph.getNum_2PEdge();

	if (twoPathedge_num <= 0) return 0.0; //denominator is 0 so skipp dividing	

	//get numerator
	int triangleNum = graph.get_Triangles();

	result = (float)triangleNum * 3 / twoPathedge_num;

	return result;
}

std::map<int, int> get_degree_distribution(Graph graph)
{
	map<int, int> histogram;

	for (int i = 0; i < graph.get_num_nodes(); i++)
		histogram[i] = 0;

	map<Node, int> degrees = graph.get_All_Degrees();

	for (auto &x : degrees)
		histogram[x.second]++;


	
	//	for (auto &x : histogram)
	//{
	//	cout << x.first << "\t";
	//	for (int i = 0; i < x.second; i++)
	//		cout << "o";
	//	cout << endl;
	//}
	

	return histogram;
}
