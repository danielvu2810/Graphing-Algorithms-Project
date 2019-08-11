#include "project3.h"

double randomDouble(double lb, double ub)
{
	mt19937 mt = mt19937(chrono::system_clock::now().time_since_epoch().count());

	uniform_real_distribution<double> ui = uniform_real_distribution<double>(lb, ub);

	double r = ui(mt);

	if (r == ub)
		r = ui(mt);

	return r;
}

Graph create_erdos_renyi_graph(int n, float p)
{
	if (p >= float(1.00)) p = randomDouble(double(0.00), double(0.99));

	if (n <= 1) return make_graph(n, { 0 }, { 0 });
	int v = 1, w = -1;
	double r=0;

	vector<int> vert1; 
	vector<int> vert2;

	int size = 0;

	map<int, bool> createdNodes;
	for (int i = 0; i < n; i++)
		createdNodes[i] = false;

	while (v < n)
	{
		r = randomDouble(0, 1);

		w += 1 + (int)(floor(log10(1 - r) / log10(1 - p)));

		while (w >= v && v < n)
		{
			w -= v;
			v++;
		}

		if (v < n)
		{
			createdNodes[v] = true;
			createdNodes[w] = true;

			vert1.push_back(v);
			vert2.push_back(w);
		}
	}

	return make_graph(n,vert1,vert2);
}