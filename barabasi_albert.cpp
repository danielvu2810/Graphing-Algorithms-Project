#include "project3.h"

int randomInt(int lb, int ub)
{
	mt19937 mt = mt19937(chrono::system_clock::now().time_since_epoch().count());

	uniform_int_distribution<int> ui = uniform_int_distribution<int>(lb, ub);

	int r = ui(mt);

	return r;
}

Graph create_barabasi_albert_graph(int n, int d)
{
	if (n < 0) n = 0;

	int size = 0;

	vector<int> vert1;
	vector<int> vert2;
	
	map<int, set<int>> mvert;

	vector<int> vectorN,vectorD;

	map<int, bool> createdNodes;
	for (int i = 0; i < 2 * n*d; i++)
		createdNodes[i] = false;

	vector<int> M(2 * n*d, 0);

	for (int i = 0; i < n; i++)
		vectorN.push_back(i);

	for (int i = 0; i < d; i++)
		vectorD.push_back(i);

	int r;

	for (int v = 0; v < n; v++) {
		for (int i = 0; i < d; i++)
		{
			M[2 * (v*d + i)] = v;
			r = randomInt(0, 2 * (v*d + i));
			M[2 * (v*d + i) + 1] = M[r];
		}
	}

	for (int i = 0; i < n*d; i++)
	{
		createdNodes[M[2 * i]] = true;
		createdNodes[M[2 * i + 1]] = true;

		mvert[M[2 * i]].insert(M[2 * i + 1]);
		//vert1.push_back(M[2 * i]);
		//vert2.push_back(M[2 * i+1]);
	}

	for (auto &x : mvert)
	{
		for (auto &y : x.second)
		{
			vert1.push_back(x.first);
			vert2.push_back(y);
		}
	}
	

	return make_graph(n, vert1, vert2);
}