#include "Matrix.hpp"
#include <numeric> // Include <numeric> header for inner_product

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

double Matrix::get(int row, int col) const {
    return data[row][col];
}

void Matrix::set(int row, int col, double value) {
    data[row][col] = value;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.set(j, i, data[i][j]);
        }
    }
    return result;
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.numRows()) throw std::invalid_argument("Matrix dimensions must agree for multiplication.");
    Matrix result(rows, other.numCols());
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.numCols(); ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.get(k, j);
            }
        }
    }
    return result;
}

Matrix Matrix::inverse() const {
    if (rows != cols) throw std::invalid_argument("Only square matrices can be inverted.");
    int n = rows;
    Matrix result(n, n);
    Matrix augment(*this);

    for (int i = 0; i < n; ++i) {
        augment.data[i].resize(2 * n);
        augment.data[i][n + i] = 1.0;
    }

    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(augment.data[k][i]) > std::abs(augment.data[maxRow][i])) {
                maxRow = k;
            }
        }
        std::swap(augment.data[i], augment.data[maxRow]);

        if (std::abs(augment.data[i][i]) < 1e-10) throw std::runtime_error("Matrix is singular and cannot be inverted.");

        for (int j = n; j < 2 * n; ++j) {
            augment.data[i][j] /= augment.data[i][i];
        }
        augment.data[i][i] = 1;

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augment.data[k][i];
                for (int j = i; j < 2 * n; ++j) {
                    augment.data[k][j] -= factor * augment.data[i][j];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result.set(i, j, augment.data[i][j + n]);
        }
    }

    return result;
}

void Matrix::qrDecompose(Matrix& Q, Matrix& R) const {
    Q = Matrix(rows, cols);
    R = Matrix(rows, cols);
    for (int k = 0; k < cols; ++k) {
        std::vector<double> u(rows);
        for (int i = 0; i < rows; ++i) {
            u[i] = get(i, k);
        }
        for (int i = 0; i < k; ++i) {
            double dot = 0.0;
            for (int j = 0; j < rows; ++j) {
                dot += Q.get(j, i) * u[j];
            }
            for (int j = 0; j < rows; ++j) {
                u[j] -= dot * Q.get(j, i);
            }
        }
        double norm = sqrt(std::inner_product(u.begin(), u.end(), u.begin(), 0.0));
        for (int i = 0; i < rows; ++i) {
            Q.set(i, k, u[i] / norm);
        }
        for (int i = k; i < cols; ++i) {
            double dot = 0.0;
            for (int j = 0; j < rows; ++j) {
                dot += Q.get(j, k) * get(j, i);
            }
            R.set(k, i, dot);
        }
    }
}

double Matrix::determinant() const {
    if (rows != cols) throw std::invalid_argument("Determinant is defined only for square matrices.");

    if (rows == 1) {
        return data[0][0];
    } else if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    } else {
        double det = 0.0;
        for (int j = 0; j < cols; ++j) {
            Matrix minor(rows - 1, cols - 1);
            for (int i = 1; i < rows; ++i) {
                for (int k = 0; k < cols; ++k) {
                    if (k < j) {
                        minor.set(i - 1, k, data[i][k]);
                    } else if (k > j) {
                        minor.set(i - 1, k - 1, data[i][k]);
                    }
                }
            }
            det += (j % 2 == 0 ? 1 : -1) * data[0][j] * minor.determinant();
        }
        return det;
    }
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (double elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

