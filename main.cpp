#include "project3.h"

#define MIN_ID 100
#define MAX_ID 1000000
#define FOLDER_DIRECTORY_ER "./data_All/"
#define FOLDER_DIRECTORY_BA "./data_All/"


struct Data
{
	int num_nodes;
	int num_edges;
	int diameter;
	float clustering_coefficients;
	map<int, int> histogram;
};

Data collectData(Graph graph)
{
	Data data;

	data.num_nodes = graph.get_num_nodes();
	data.num_edges = graph.get_num_edges();

	cout << "test " << data.num_nodes << " nodes & " << data.num_edges << " edges:\nget_degree_distribution: ";
	
	data.histogram = get_degree_distribution(graph);
	cout << "completed\nget_diameter: ";

	data.diameter = get_diameter(graph);
	cout << "completed\nget_clustering_coefficient: ";

	data.clustering_coefficients = get_clustering_coefficient(graph);
	cout << "completed\n";


	return data;
}

void create_erdos_renyi_Files(const string folder, const string size)
{
	ofstream f;
	f.open(folder + "er_info.csv", ios::trunc);
	f << "Size,Edges\n";
	f.close();

	f.open(folder + "er_diameter.csv", ios::trunc);
	f << "Size,Diameter\n";
	f.close();

	f.open(folder + "er_clustering.csv", ios::trunc);
	f << "Size,Clustering Coefficient\n";
	f.close();

	f.open(folder + size + "_" + "er_degree.csv", ios::trunc);
	f << "Degree,Frequency\n";
	f.close();
}

void create_barabasi_albert_Files(const string folder, const string size)
{
	ofstream f;

	f.open(folder + "ba_info.csv", ios::trunc);
	f << "Size,Edges\n";
	f.close();

	f.open(folder + "ba_clustering.csv", ios::trunc);
	f << "Size,Clustering Coefficient\n";
	f.close();

	f.open(folder + size +  "_" + "ba_degree.csv", ios::trunc);
	f << "Degree,Frequency\n";
	f.close();
}

void create_All_Files(int j)
{
	string size = to_string(j);

	create_erdos_renyi_Files(FOLDER_DIRECTORY_ER, size);

	create_barabasi_albert_Files(FOLDER_DIRECTORY_BA, size);
}

void add_data_to_erdos_renyi_Files(const string folder, const string size, const Data data)
{
	ofstream f;

	f.open(folder + "er_info.csv", ios::app);
	f << data.num_nodes << "," << data.num_edges << "\n";
	f.close();

	f.open(folder + "er_diameter.csv", ios::app);
	f << data.num_nodes << "," << data.diameter << "\n";
	f.close();

	f.open(folder + "er_clustering.csv", ios::app);
	f << data.num_nodes << "," << data.clustering_coefficients << "\n";
	f.close();

	f.open(folder + size + "_" + "er_degree.csv", ios::app);
	for (auto &x : data.histogram)
		f << x.first << "," << x.second << "\n";
	f.close();
}

void add_data_to_barabasi_albert_Files(const string folder, const string size, const Data data)
{
	ofstream f;

	f.open(folder + "ba_info.csv", ios::app);
	f << data.num_nodes << "," << data.num_edges << "\n";
	f.close();

	f.open(folder + "ba_diameter.csv", ios::app);
	f << data.num_nodes << "," << data.diameter << "\n";
	f.close();

	f.open(folder + "ba_clustering.csv", ios::app);
	f << data.num_nodes << "," << data.clustering_coefficients << "\n";
	f.close();

	f.open(folder + size + "_" + "ba_degree.csv", ios::app);
	for (auto &x : data.histogram)
		f << x.first << "," << x.second << "\n";

	f.close();
}

void run_erdos_renyi_test(int j)
{
	Graph graph;

	string size = to_string(j);

	cout << "\n\n--- Erdos_Renyi ---"<<" Size " << j;

	cout << "\n\ncreate_er_graph -> ";

	graph = create_erdos_renyi_graph(j, (float)(2 * log(j) / j));

	cout << "add_to_er_files -> ";

	Data data = collectData(graph);

	add_data_to_erdos_renyi_Files(FOLDER_DIRECTORY_ER, size, data);

}

void run_barabasi_albert_test(int j)
{
	Graph graph;

	string size, test;

	size = to_string(j);

	cout << "\n\n--- Barabasi_Albert ---" <<" Size " << j;

	cout << "\n\ncreate_ba_graph -> ";

	graph = create_barabasi_albert_graph(j, 5);

	cout << "add_to_ba_files -> ";

	Data data = collectData(graph);

	add_data_to_barabasi_albert_Files(FOLDER_DIRECTORY_BA, size, data );
}

void run_and_print_to_Files()
{
	for (int j = MIN_ID; j <= MAX_ID; j *= 10)
	{
			create_All_Files(j);

			if(j*5<=MAX_ID)
			create_All_Files(j * 5);
	}
	
	for (int j = MIN_ID; j <= MAX_ID; j *= 10)
	{
			run_erdos_renyi_test(j);

			run_barabasi_albert_test(j);
		
			if (j * 5 <= MAX_ID)
			{
				run_erdos_renyi_test(j * 5);

				run_barabasi_albert_test(j * 5);
			}
	}
}

int main()
{
	run_and_print_to_Files();
	
	return 0;
}
