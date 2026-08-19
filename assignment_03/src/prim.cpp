#include "mst.h"
#include <queue>

using namespace std;

long long primMST(const Csr& graph, vector<Edge>& mstEdges) {
    mstEdges.clear();
    int V = graph.csrGraph.numVertices;
    if (V == 0) return 0;
    long long totalWeight = 0;
    vector<bool> inMST(V, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    inMST[0] = true;
    int startIdx = graph.csrGraph.rowPtr[0];
    int endIdx = graph.csrGraph.rowPtr[1];
    for (int i = startIdx; i < endIdx; i++) {
        pq.push({0, graph.csrGraph.colIdx[i], graph.csrGraph.values[i]});
    }

    int edgesSelected = 0;
    while (!pq.empty() && edgesSelected < V - 1) {
        Edge curr = pq.top();
        pq.pop();
        int u = curr.u;
        int v = curr.v;
        int weight = curr.weight;
        if (inMST[v]) continue;
        inMST[v] = true;
        mstEdges.push_back({u, v, weight});
        totalWeight += weight;
        edgesSelected++;
        int vStart = graph.csrGraph.rowPtr[v];
        int vEnd = graph.csrGraph.rowPtr[v + 1];
        for (int i = vStart; i < vEnd; i++) {
            int neighbor = graph.csrGraph.colIdx[i];
            int nWeight = graph.csrGraph.values[i];
            if (!inMST[neighbor]) {
                pq.push({v, neighbor, nWeight});
            }
        }
    }
    return totalWeight;
}