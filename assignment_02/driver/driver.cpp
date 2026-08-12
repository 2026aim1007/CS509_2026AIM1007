#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

#include "../../utility/csr.h"
#include "../../utility/testing_utils.h"
#include "../src/graph_algorithms.h"

using namespace std;

bool parseFWMatrix(const string& filename, int& V, vector<vector<long long>>& matrix) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return false;
    inFile >> V;
    matrix.assign(V, vector<long long>(V, INF));
    string val;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            inFile >> val;
            if (val != "INF") {
                matrix[i][j] = stoll(val);
            }
        }
    }
    return true;
}

int getBellmanFordSource(const string& filename) {
    ifstream inFile(filename);
    string line, lastLine;
    while (getline(inFile, line)) {
        if (!line.empty()) lastLine = line;
    }
    stringstream ss(lastLine);
    string token;
    int source = 0;
    ss >> token >> source;
    return source;
}

int main(int argc, char* argv[]) {
    int choice;
    string runMode = "ALL";
    bool isBenchmarkMode = false;
    if (argc >= 3) {
        choice = stoi(argv[1]);
        runMode = argv[2];
        if (argc >= 4 && string(argv[3]) == "--test") {
            isBenchmarkMode = true;
        }
    } else {
        cout << "=================================================\n";
        cout << "      CS509 Solo Assgn 2 Driver (BF, FW)\n";
        cout << "=================================================\n\n";
        cout << "Select Algorithm:\n";
        cout << "1. Bellman-Ford (BF)\n";
        cout << "2. Floyd-Warshall (FW)\n";
        cout << "Enter choice (1-2): ";
        cin >> choice;
        
        char modeFlag;
        cout << "Run in Benchmark mode? (y/n - averages 5 runs): ";
        cin >> modeFlag;
        if (modeFlag == 'y' || modeFlag == 'Y') isBenchmarkMode = true;
    }

    if (choice < 1 || choice > 2) {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    int iterations = isBenchmarkMode ? 5 : 1;
    vector<string> graphSizes;
    
    if (runMode == "ALL") {
        if (choice == 1) { // BF Sizes
            graphSizes = {"10", "100", "10000", "50000", "100000"}; 
        } else {           // FW Reduced Sizes
            graphSizes = {"10", "100", "500", "1000", "2000"};
        }
    } else {
        graphSizes = {runMode};
    }

    for (const string& sizeStr : graphSizes) {
        cout << "\n>>> Running Test Case: " << sizeStr << " Vertices <<<\n";
        
        string algoPrefix = (choice == 1) ? "bf" : "fw";
        string testPath = "tests/" + algoPrefix + "_" + sizeStr + ".txt";
        string outPath = "outputs/output_" + algoPrefix + "_" + sizeStr + ".txt";
        string expPath = "outputs/expected_" + algoPrefix + "_" + sizeStr + ".txt";

        double avgTimeMs = 0.0;
        ofstream outFile(outPath);
        
        if (choice == 1) { // Bellman-Ford
            Csr graph;
            graph.convert(testPath, true); // Pass true if graph is directed
            
            // Validate graph loaded successfully instead of checking convert() return
            if (graph.csrGraph.numVertices == 0) { 
                cout << "  [!] Error: Could not load " << testPath << "\n";
                continue;
            }
            
            int source = getBellmanFordSource(testPath);
            vector<long long> distances;
            bool hasNegativeCycle = false;
            
            auto algoLambda = [&]() { 
                distances.clear(); 
                hasNegativeCycle = bellmanFord(graph, source, distances); 
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            
            outFile << "Algorithm: Bellman-Ford\n";
            outFile << "Source: " << source << "\n";
            
            if (hasNegativeCycle) {
                outFile << "Negative cycle: true\n";
            } else {
                outFile << "Vertex Distance\n";
                for (size_t i = 0; i < distances.size(); i++) {
                    outFile << i << " ";
                    if (distances[i] == INF) outFile << "INF\n";
                    else outFile << distances[i] << "\n";
                }
                outFile << "Negative cycle: none\n";
            }
        } 
        else if (choice == 2) { // Floyd-Warshall
            int V;
            vector<vector<long long>> distMatrix;
            if (!parseFWMatrix(testPath, V, distMatrix)) {
                cout << "  [!] Error: Could not load " << testPath << "\n";
                continue;
            }
            bool hasNegativeCycle = false;
            
            auto algoLambda = [&]() { 
                hasNegativeCycle = floydWarshall(V, distMatrix); 
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            
            outFile << "Algorithm: Floyd-Warshall\n";
            if (hasNegativeCycle) {
                outFile << "Negative cycle: true\n";
            } else {
                outFile << "Distance matrix:\n";
                for (int i = 0; i < V; i++) {
                    for (int j = 0; j < V; j++) {
                        if (distMatrix[i][j] == INF) outFile << "INF ";
                        else outFile << distMatrix[i][j] << " ";
                    }
                    outFile << "\n";
                }
                outFile << "Negative cycle: none\n";
            }
        }

        outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
        outFile << "Execution time: " << avgTimeMs << " ms\n";
        if (isBenchmarkMode) outFile << "(Averaged over " << iterations << " runs)\n";
        outFile.close();

        cout << "--- " << algoPrefix << " TEST SUMMARY ---\n";
        if (compareFilesWithEscape(outPath, expPath)) {
            cout << "Status: PASSED\n";
        } else {
            cout << "Status: FAILED (Check " << outPath << " against expected)\n";
        }
        cout << (isBenchmarkMode ? "Avg Time: " : "Time: ") << avgTimeMs << " ms\n";
    }
    
    return 0;
}