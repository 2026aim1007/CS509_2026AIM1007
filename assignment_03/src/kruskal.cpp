#include "mst.h"
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            return true;
        }
        return false;
    }
};

long long kruskalMST(const Csr& graph, vector<Edge>& mstEdges) {
    mstEdges.clear();
    int V = graph.csrGraph.numVertices;
    vector<Edge> allEdges;
    for (int u = 0; u < V; u++) {
        int start = graph.csrGraph.rowPtr[u];
        int end = graph.csrGraph.rowPtr[u + 1];
        for (int i = start; i < end; i++) {
            int v = graph.csrGraph.colIdx[i];
            int weight = graph.csrGraph.values[i];
            if (u < v) {
                allEdges.push_back({u, v, weight});
            }
        }
    }
    sort(allEdges.begin(), allEdges.end());
    DSU dsu(V);
    long long totalWeight = 0;
    for (const Edge& edge : allEdges) {
        if (dsu.unite(edge.u, edge.v)) {
            mstEdges.push_back(edge);
            totalWeight += edge.weight;
            if (mstEdges.size() == (size_t)V - 1) break;
        }
    }
    return totalWeight;
}