#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include "../src/gemm.h"

using namespace std;
using namespace std::chrono;

bool compareFiles(const string& p1, const string& p2) {
    ifstream f1(p1), f2(p2);
    if (!f1.is_open() || !f2.is_open()) return false;
    string w1, w2;
    
    while (f1 >> w1 && f2 >> w2) {
        if (w1 != w2) return false;
    }
    return (bool)(f1 >> w1) == (bool)(f2 >> w2); 
}

void printMatrix(const Matrix& C, ostream& out) {
    for (int i = 0; i < C.rows; i++) {
        for (int j = 0; j < C.cols; j++) {
            out << C.data[i][j] << (j == C.cols - 1 ? "" : " ");
        }
        out << "\n";
    }
}

int main() {
    cout << "=================================================\n";
    cout << "          Assignment 1 GEMM Automated Testing           \n";
    cout << "=================================================\n\n";

    for (int i = 1; i <= 5; i++) {
        string testId = "0" + to_string(i);
        string testFilePath = "tests/test_" + testId + ".txt";
        string outFilePath = "outputs/output_" + testId + ".txt";
        string expectedFilePath = "outputs/expected_" + testId + ".txt";

        cout << ">>> Running Test Case " << i << " (" << testFilePath << ")\n";

        ifstream file(testFilePath);
        if (!file.is_open()) {
            cout << "  [!] Error: Could not open test file " << testFilePath << "\n\n";
            continue;
        }

        int M, K, N;
        if (!(file >> M >> K >> N)) {
            cout << "  [!] Error: Invalid file format.\n\n";
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
        
        ofstream outFile(outFilePath);
        if (!outFile.is_open()) {
            cout << "  [!] Error: Could not create output file.\n\n";
            continue;
        }

        // Simple Matrix Multiplication
        auto start_simple = high_resolution_clock::now();
        Matrix C_simple = gemm_simple(A, B);
        auto stop_simple = high_resolution_clock::now();
        auto duration_simple = duration_cast<milliseconds>(stop_simple - start_simple);
        
        cout << "Algorithm: GEMM Simple\nResult matrix:\n";
        outFile << "Algorithm: GEMM Simple\nResult matrix:\n";
        
        printMatrix(C_simple, outFile);
        cout << "Execution time: " << duration_simple.count() << " ms\n\n";

        // Blocking Matrix Multiplication
        int blockSize =  64; // block size for blocking algorithm
        auto start_blocking = high_resolution_clock::now();
        Matrix C_blocking = gemm_blocking(A, B, blockSize);
        auto stop_blocking = high_resolution_clock::now();
        auto duration_blocking = duration_cast<milliseconds>(stop_blocking - start_blocking);
        
        cout << "Algorithm: GEMM Blocking\nResult matrix:\n";
        outFile << "Algorithm: GEMM Blocking\nResult matrix:\n";
        
        printMatrix(C_blocking, outFile);
        cout << "Execution time: " << duration_blocking.count() << " ms\n\n";

        outFile.close();

        cout << "--- TEST " << i << " SUMMARY ---\n";
        if (compareFiles(outFilePath, expectedFilePath)) {
            cout << "Status: PASSED\n";
        } else {
            cout << "Status: FAILED\n";
        }
        cout << "Simple GEMM Time  : " << duration_simple.count() << " ms\n";
        cout << "Blocking GEMM Time: " << duration_blocking.count() << " ms\n";
        cout << "=================================================\n\n";
    }

    return 0;
}