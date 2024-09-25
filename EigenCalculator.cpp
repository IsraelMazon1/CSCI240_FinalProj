#include "EigenCalculator.hpp"

std::vector<double> EigenCalculator::computeEigenvalues(const Matrix& matrix) {
    Matrix A = matrix; // Copy of matrix for eigenvalue computation
    int n = A.numRows();
    Matrix Q(n, n), R(n, n);

    for (int i = 0; i < 100; ++i) { // 100 iterations as a simple convergence criterion
        A.qrDecompose(Q, R);
        A = R.multiply(Q);
    }

    std::vector<double> eigenvalues(n);
    for (int i = 0; i < n; ++i) {
        eigenvalues[i] = A.get(i, i);
    }
    return eigenvalues;
}

