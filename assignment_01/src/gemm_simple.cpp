#include "gemm.h"

Matrix gemm_simple(const Matrix& A, const Matrix& B) {
    Matrix C;
    C.rows = A.rows;
    C.cols = B.cols;
    C.data.assign(C.rows, vector<int>(C.cols, 0));
    for (int i = 0; i < A.rows; i++) {
        for (int k = 0; k < A.cols; k++) {
            int r = A.data[i][k];
            for (int j = 0; j < B.cols; j++) {
                C.data[i][j] += r * B.data[k][j];
            }
        }
    }
    
    return C;
}