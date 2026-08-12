#include "graph_algorithms.h"

using namespace std;

bool floydWarshall(int V, vector<vector<long long>>& distMatrix) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            if (distMatrix[i][k] == INF) continue;
            for (int j = 0; j < V; j++) {
                if (distMatrix[k][j] == INF) continue;
                if (distMatrix[i][k] + distMatrix[k][j] < distMatrix[i][j]) {
                    distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
                }
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (distMatrix[i][i] < 0) {
            return true;
        }
    }
    return false;
}