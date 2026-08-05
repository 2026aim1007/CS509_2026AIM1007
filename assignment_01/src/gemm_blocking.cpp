#include "gemm.h"
#include <algorithm>

Matrix gemm_blocking(const Matrix& A, const Matrix& B, int blockSize) {
    Matrix C;
    C.rows = A.rows;
    C.cols = B.cols;
    C.data.assign(C.rows, vector<int>(C.cols, 0));
    for (int ii = 0; ii < A.rows; ii += blockSize) {
        for (int kk = 0; kk < A.cols; kk += blockSize) {
            for (int jj = 0; jj < B.cols; jj += blockSize) {
                for (int i = ii; i < std::min(ii + blockSize, A.rows); i++) {
                    for (int k = kk; k < std::min(kk + blockSize, A.cols); k++) {
                        int r = A.data[i][k];
                        for (int j = jj; j < std::min(jj + blockSize, B.cols); j++) {
                            C.data[i][j] += r * B.data[k][j];
                        }
                    }
                }
                
            }
        }
    }
    
    return C;
}