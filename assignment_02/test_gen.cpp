#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>

#include "../utility/csr.h"
#include "src/graph_algorithms.h"

using namespace std;

void createDirectories() {
#ifdef _WIN32
    system("if not exist tests mkdir tests");
    system("if not exist outputs mkdir outputs");
#else
    system("mkdir -p tests outputs");
#endif
}

void generateBF(int V) {
    vector<vector<pair<int, int>>> adj(V);
    int E = 0;
    
    for (int i = 0; i < V; i++) {
        int outDegree = rand() % 4 + 1; // 1 to 4 edges per vertex
        for (int k = 0; k < outDegree; k++) {
            if (i < V - 1) {
                int j = i + 1 + (rand() % (V - 1 - i)); 
                int weight = (rand() % 40) - 10;
                adj[i].push_back({j, weight});
                E++;
            }
        }
    }

    string testId = to_string(V);
    string inputPath = "tests/bf_" + testId + ".txt";
    ofstream inFile(inputPath);
    inFile << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        inFile << i << " " << adj[i].size();
        for (auto& edge : adj[i]) {
            inFile << " " << edge.first << " " << edge.second;
        }
        inFile << "\n";
    }
    inFile << "SOURCE 0\n";
    inFile.close();
    Csr graph;
    graph.convert(inputPath, true);
    vector<long long> distances;
    bool hasNegCycle = bellmanFord(graph, 0, distances);

    string expectedPath = "outputs/expected_bf_" + testId + ".txt";
    ofstream expFile(expectedPath);
    expFile << "Algorithm: Bellman-Ford\nSource: 0\n";
    
    if (hasNegCycle) {
        expFile << "Negative cycle: true\n";
    } else {
        expFile << "Vertex Distance\n";
        for (size_t i = 0; i < distances.size(); i++) {
            expFile << i << " ";
            if (distances[i] == INF) expFile << "INF\n";
            else expFile << distances[i] << "\n";
        }
        expFile << "Negative cycle: none\n";
    }
    expFile.close();

    cout << "[+] Generated & Executed BF for V = " << V << "\n";
}

void generateFW(int V) {
    vector<vector<long long>> matrix(V, vector<long long>(V, INF));
    for (int i = 0; i < V; i++) {
        matrix[i][i] = 0;
        for (int j = 0; j < V; j++) {
            if (i != j && rand() % 4 == 0) {
                matrix[i][j] = (rand() % 50) + 1;
            }
        }
    }

    string testId = to_string(V);
    string inputPath = "tests/fw_" + testId + ".txt";
    ofstream inFile(inputPath);
    inFile << V << "\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INF) inFile << "INF ";
            else inFile << matrix[i][j] << " ";
        }
        inFile << "\n";
    }
    inFile.close();
    bool hasNegCycle = floydWarshall(V, matrix);
    string expectedPath = "outputs/expected_fw_" + testId + ".txt";
    ofstream expFile(expectedPath);
    expFile << "Algorithm: Floyd-Warshall\n";
    
    if (hasNegCycle) {
        expFile << "Negative cycle: true\n";
    } else {
        expFile << "Distance matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (matrix[i][j] == INF) expFile << "INF ";
                else expFile << matrix[i][j] << " ";
            }
            expFile << "\n";
        }
        expFile << "Negative cycle: none\n";
    }
    expFile.close();

    cout << "[+] Generated & Executed FW for V = " << V << "\n";
}

int main() {
    createDirectories();
    generateBF(10);
    generateBF(100);
    generateBF(10000);
    generateBF(50000);
    generateBF(100000);
    generateFW(10);
    generateFW(100);
    generateFW(500);
    generateFW(1000);
    generateFW(2000);   
    return 0;
}