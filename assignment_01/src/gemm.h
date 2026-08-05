#ifndef GEMM_H
#define GEMM_H

#include <vector>
using namespace std;

struct Matrix {
    int rows = 0;
    int cols = 0;
    vector<vector<int>> data;
};

Matrix gemm_simple(const Matrix& A, const Matrix& B);
Matrix gemm_blocking(const Matrix& A, const Matrix& B, int blockSize);

#endif // GEMM_H