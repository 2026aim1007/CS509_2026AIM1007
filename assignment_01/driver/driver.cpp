#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "../../utility/testing_utils.h"
#include "../src/gemm.h"

using namespace std;

void printMatrix(const Matrix& C, ostream& out) {
    for (int i = 0; i < C.rows; i++) {
        for (int j = 0; j < C.cols; j++) {
            out << C.data[i][j] << (j == C.cols - 1 ? "" : " ");
        }
        out << "\n";
    }
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
        cout << "      CS509 Solo Assgn 1 Driver (GEMM)\n";
        cout << "=================================================\n\n";
        cout << "Select Algorithm:\n";
        cout << "1. GEMM Simple\n";
        cout << "2. GEMM Blocking\n";
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
    vector<string> testIds;
    if (runMode == "ALL") {
        testIds = {"01", "02", "03", "04", "05"};
    } else {
        if (runMode.length() == 1) runMode = "0" + runMode;
        testIds = {runMode};
    }
    for (const string& testId : testIds) {
        cout << "\n>>> Running Test Case: " << testId << " <<<\n";
        string testPath = "tests/test_" + testId + ".txt";
        string outPath = "outputs/output_" + testId + ".txt";
        string expPath = "outputs/expected_" + testId + ".txt";
        ifstream file(testPath);
        if (!file.is_open()) {
            cout << "  [!] Error: Could not open test file " << testPath << "\n";
            continue;
        }
        int M, K, N;
        if (!(file >> M >> K >> N)) {
            cout << "  [!] Error: Invalid file format in " << testPath << "\n";
            continue;
        }
        Matrix A;
        A.rows = M; A.cols = K; A.data.assign(M, vector<int>(K));
        for (int row = 0; row < M; row++) {
            for (int col = 0; col < K; col++) file >> A.data[row][col];
        }
        Matrix B;
        B.rows = K; B.cols = N; B.data.assign(K, vector<int>(N));
        for (int row = 0; row < K; row++) {
            for (int col = 0; col < N; col++) file >> B.data[row][col];
        }
        file.close();
        Matrix C;
        double avgTimeMs = 0.0;
        if (choice == 1) { // GEMM Simple
            auto algoLambda = [&]() { C = gemm_simple(A, B); };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
        } 
        else if (choice == 2) { // GEMM Blocking
            int blockSize = 64; 
            auto algoLambda = [&]() { C = gemm_blocking(A, B, blockSize); };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
        }
        ofstream outFile(outPath);
        if (!outFile.is_open()) {
            cout << "  [!] Error: Could not create output file.\n";
            continue;
        }
        string algoName = (choice == 1) ? "GEMM Simple" : "GEMM Blocking";
        outFile << "Algorithm: " << algoName << "\nResult matrix:\n";
        printMatrix(C, outFile);
        outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
        outFile << "Execution time: " << avgTimeMs << " ms\n";
        if (isBenchmarkMode) outFile << "(Averaged over " << iterations << " runs)\n";
        outFile.close();
        cout << "--- " << algoName << " TEST SUMMARY ---\n";
        if (compareFilesWithEscape(outPath, expPath)) {
            cout << "Status: PASSED\n";
        } else {
            cout << "Status: FAILED (Check " << outPath << " against expected)\n";
        }
        cout << (isBenchmarkMode ? "Avg Time: " : "Time: ") << avgTimeMs << " ms\n";
    }

    return 0;
}