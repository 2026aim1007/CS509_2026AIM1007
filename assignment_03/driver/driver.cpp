#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../src/mst.h"
#include "../../utility/testing_utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    string runMode = "ALL";
    bool isBenchmarkMode = false;
    if (argc >= 2) {
        runMode = argv[1];
        if (argc >= 3 && string(argv[2]) == "--test") {
            isBenchmarkMode = true;
        }
    } else {
        cout << "=================================================\n";
        cout << "      CS509 Assignment 3 - MST Driver            \n";
        cout << "=================================================\n\n";
        char modeFlag;
        cout << "Run in Benchmark mode? (y/n - averages 5 runs): ";
        cin >> modeFlag;
        if (modeFlag == 'y' || modeFlag == 'Y') isBenchmarkMode = true;
        cout << "\n";
    }
    int iterations = isBenchmarkMode ? 5 : 1;
    vector<string> graphSizes;
    if (runMode == "ALL") {
        graphSizes = {"10", "100", "10000", "50000", "100000"};
    } else {
        graphSizes = {runMode};
    }
    for (const string& sizeStr : graphSizes) {
        cout << ">>> Running Test Case: " << sizeStr << " Vertices <<<\n";
        string testFilePath = "tests/mst_" + sizeStr + ".txt";
        string outFilePath = "outputs/output_mst_" + sizeStr + ".txt";
        string expectedFilePath = "outputs/expected_mst_" + sizeStr + ".txt";
        Csr graph;
        graph.convert(testFilePath, true); 
        if (graph.csrGraph.numVertices == 0) {
            cout << "  [!] Error: Could not load graph from " << testFilePath << "\n\n";
            continue;
        }
        vector<Edge> kruskalEdges, primEdges;
        long long kruskalWeight = 0, primWeight = 0;
        double kruskalTimeMs = 0.0, primTimeMs = 0.0;
        auto kruskalLambda = [&]() {
            kruskalWeight = kruskalMST(graph, kruskalEdges);
        };
        kruskalTimeMs = measureAverageExecutionTime(kruskalLambda, iterations);
        auto primLambda = [&]() {
            primWeight = primMST(graph, primEdges);
        };
        primTimeMs = measureAverageExecutionTime(primLambda, iterations);
        ofstream outFile(outFilePath);
        if (outFile.is_open()) {
            bool printEdges = (sizeStr == "10" || sizeStr == "100");
            outFile << "Algorithm: Kruskal's MST\n";
            if (printEdges) {
                outFile << "MST edges:\n";
                for (const auto& e : kruskalEdges) outFile << e.u << " " << e.v << " " << e.weight << "\n";
            } else {
                outFile << "(Edges hidden for large graph)\n";
            }
            outFile << "Total MST weight: " << kruskalWeight << "\n\n";
            outFile << "Algorithm: Prim's MST\n";
            if (printEdges) {
                outFile << "MST edges:\n";
                for (const auto& e : primEdges) outFile << e.u << " " << e.v << " " << e.weight << "\n";
            } else {
                outFile << "(Edges hidden for large graph)\n";
            }
            outFile << "Total MST weight: " << primWeight << "\n";
            outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
            outFile << "Kruskal Execution time: " << kruskalTimeMs << " ms\n";
            outFile << "Prim Execution time: " << primTimeMs << " ms\n";
            if (isBenchmarkMode) {
                outFile << "(Averaged over " << iterations << " runs)\n";
            }
            outFile << "Status: " << (kruskalWeight == primWeight ? "MATCH" : "MISMATCH") << "\n";
            outFile.close();
        }
        cout << "--- MST TEST SUMMARY (mst_" << sizeStr << ") ---\n";
        if (compareFilesWithEscape(outFilePath, expectedFilePath)) {
            cout << "Output Status: PASSED (Matches Expected File)\n";
        } else {
            cout << "Output Status: FAILED (Check " << outFilePath << " against expected)\n";
        }
        if (kruskalWeight == primWeight) {
            cout << "Algorithm Status: PASSED (Kruskal and Prim Weights Equal)\n";
        } else {
            cout << "Algorithm Status: FAILED (Weight Mismatch!)\n";
        }
        cout << "Kruskal Weight: " << kruskalWeight << " | Time: " << kruskalTimeMs << " ms\n";
        cout << "Prim Weight:    " << primWeight << " | Time: " << primTimeMs << " ms\n";
        cout << "=================================================\n\n";
    }
    return 0;
}