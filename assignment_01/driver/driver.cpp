#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
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
    string testFilePath = "../tests/test_01.txt";
    string outFilePath = "../outputs/output_01.txt";
    string expectedFilePath = "../outputs/expected_01.txt";

    ifstream file(testFilePath);
    if (!file.is_open()) {
        cout << "Error: Could not open test file " << testFilePath << "\n";
        return 1;
    }

    int M, K, N;
    if (!(file >> M >> K >> N)) {
        cout << "Error: Invalid file format.\n";
        return 1;
    }

    Matrix A;
    A.rows = M; A.cols = K; A.data.assign(M, vector<int>(K));
    for (int i = 0; i < M; i++) {
        for (int k = 0; k < K; k++) file >> A.data[i][k];
    }

    Matrix B;
    B.rows = K; B.cols = N; B.data.assign(K, vector<int>(N));
    for (int k = 0; k < K; k++) {
        for (int n = 0; n < N; n++) file >> B.data[k][n];
    }
    
    file.close();
    ofstream outFile(outFilePath);
    if (!outFile.is_open()) {
        cout << "Error: Could not create output file. Does the 'outputs' folder exist?\n";
        return 1;
    }

    // --- Simple Matrix Multiplication ---
    auto start_simple = high_resolution_clock::now();
    Matrix C_simple = gemm_simple(A, B);
    auto stop_simple = high_resolution_clock::now();
    auto duration_simple = duration_cast<milliseconds>(stop_simple - start_simple);
    
    cout << "Algorithm: GEMM Simple\nResult matrix:\n";
    outFile << "Algorithm: GEMM Simple\nResult matrix:\n";
    
    printMatrix(C_simple, cout);
    printMatrix(C_simple, outFile);
    cout << "Execution time: " << duration_simple.count() << " ms\n\n";

    int blockSize = 2;
    auto start_blocking = high_resolution_clock::now();
    Matrix C_blocking = gemm_blocking(A, B, blockSize);
    auto stop_blocking = high_resolution_clock::now();
    auto duration_blocking = duration_cast<milliseconds>(stop_blocking - start_blocking);
    
    cout << "Algorithm: GEMM Blocking\nResult matrix:\n";
    outFile << "Algorithm: GEMM Blocking\nResult matrix:\n";
    
    printMatrix(C_blocking, cout);
    printMatrix(C_blocking, outFile);
    
    cout << "Execution time: " << duration_blocking.count() << " ms\n\n";

    outFile.close();

    if (compareFiles(outFilePath, expectedFilePath)) {
        cout << "--- TEST CASE HAS PASSED ---\n";
    } else {
        cout << "--- TEST CASE HAS FAILED ---\n";
    }

    return 0;
}