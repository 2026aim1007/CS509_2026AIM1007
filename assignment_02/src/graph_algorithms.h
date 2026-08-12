#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <vector>
#include "../../utility/csr.h"

using namespace std;

const long long INF = 1e15; 
bool bellmanFord(const Csr& graph, int source, vector<long long>& distances);
bool floydWarshall(int V, vector<vector<long long>>& distMatrix);

#endif