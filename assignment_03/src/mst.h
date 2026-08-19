#ifndef MST_H
#define MST_H
#include <vector>
#include "../../utility/csr.h"

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};
long long kruskalMST(const Csr& graph, std::vector<Edge>& mstEdges);
long long primMST(const Csr& graph, std::vector<Edge>& mstEdges);

#endif