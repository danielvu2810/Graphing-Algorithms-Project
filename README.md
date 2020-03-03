Graphing Project involves testing various graph algorithms experimentally to determine properties of models of real-world networks. The specific graph algorithms you should implement are the following three algorithms (please see the course notes for details on these algorithms):

Diameter algorithm, that is, as best is reasonably possible, determine the length of a longest path in the graph.
Clustering-coefficient algorithm, that is, determine the ratio of three times the number of triangles over the number of paths of length 2.
Degree-distribution algorithm, that is, determine for each possible degree, the number of vertices in the graph with that degree.
You need to test each algorithm on graphs of the following type (depending on your student ID):

You should test the above algorithms on Erdos-Renyi random graphs, G(n,p), with p = 2(ln n)/n, where "ln n" denotes the natural logarithm of n.
You should test the above algorithms on Barabasi-Albert random graphs, generated with the parameter d = 5 as the number of neighbors each new vertex chooses.
You should determine the diameter and clustering coefficients of multiple random graphs of length n, and have n grow, and then plot the average diamters and clustering coefficients, respectively, as a function of n, on a lin-log scale. You should then make a determination as to whether these values grow, decrease, or remain constant as a function of n. Also, if they grow, determine if they grow proporitonal to the function, log n, or according to a function that grows faster or slower than the function, log n.

For each number of vertices, n=1,000, n=10,000, and n=100,000, plot the degree distribution of an instance of your chosen type of random graph having that number of vertices. You should plot the degree-distribution results on a regular (lin-lin) scale and a log-log scale, and then make a determination whether that degree distribution has a power law. If you decide that the degree distribution has a power law, find the slope of a line fitting the data in the log-log scale and report on the exponent of that power law.
