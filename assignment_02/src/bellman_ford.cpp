#include "graph_algorithms.h"

using namespace std;

bool bellmanFord(const Csr& graph, int source, vector<long long>& distances) {
    int V = graph.csrGraph.numVertices;
    distances.assign(V, INF);
    distances[source] = 0;
    for (int i = 0; i < V - 1; i++) {
        bool updated = false;
        for (int u = 0; u < V; u++) {
            if (distances[u] == INF) continue;
            int start = graph.csrGraph.rowPtr[u];
            int end = graph.csrGraph.rowPtr[u + 1];
            for (int j = start; j < end; j++) {
                int v = graph.csrGraph.colIdx[j];
                int weight = graph.csrGraph.values[j];
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    for (int u = 0; u < V; u++) {
        if (distances[u] == INF) continue;
        int start = graph.csrGraph.rowPtr[u];
        int end = graph.csrGraph.rowPtr[u + 1];
        for (int j = start; j < end; j++) {
            int v = graph.csrGraph.colIdx[j];
            int weight = graph.csrGraph.values[j];
            if (distances[u] + weight < distances[v]) {
                return true;
            }
        }
    }
    return false;
}