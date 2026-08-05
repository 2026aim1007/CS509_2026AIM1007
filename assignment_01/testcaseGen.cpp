#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

void generateTest(int size, string testId) {
    int M = size, K = size, N = size;
    vector<vector<int>> A(M, vector<int>(K));
    vector<vector<int>> B(K, vector<int>(N));
    vector<vector<int>> C(M, vector<int>(N, 0));

    for (int i = 0; i < M; i++)
        for (int k = 0; k < K; k++)
            A[i][k] = rand() % 10;

    for (int k = 0; k < K; k++)
        for (int n = 0; n < N; n++)
            B[k][n] = rand() % 10;

    for (int i = 0; i < M; i++)
        for (int k = 0; k < K; k++)
            for (int j = 0; j < N; j++)
                C[i][j] += A[i][k] * B[k][j];

    string testPath = "tests/test_" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << M << " " << K << " " << N << "\n";
    for (int i = 0; i < M; i++) {
        for (int k = 0; k < K; k++) tFile << A[i][k] << (k == K - 1 ? "" : " ");
        tFile << "\n";
    }
    for (int k = 0; k < K; k++) {
        for (int n = 0; n < N; n++) tFile << B[k][n] << (n == N - 1 ? "" : " ");
        tFile << "\n";
    }
    tFile.close();

    string expectedPath = "outputs/expected_" + testId + ".txt";
    ofstream eFile(expectedPath);
    
    eFile << "Algorithm: GEMM Simple\nResult matrix:\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) eFile << C[i][j] << (j == N - 1 ? "" : " ");
        eFile << "\n";
    }
    
    eFile << "Algorithm: GEMM Blocking\nResult matrix:\n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) eFile << C[i][j] << (j == N - 1 ? "" : " ");
        eFile << "\n";
    }
    eFile.close();
    cout << "Generated " << testPath << " and " << expectedPath << "\n";
}

int main() {
    cout << "Generating test files...\n";
    generateTest(4,   "01");
    generateTest(16,  "02");
    generateTest(64,  "03");
    generateTest(256, "04");
    generateTest(1024, "05");
    cout << "Done! You can now delete this generator file.\n";
    return 0;
}