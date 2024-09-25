#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;

public:
    Matrix(int rows, int cols);
    double get(int row, int col) const;
    void set(int row, int col, double value);
    int numRows() const { return rows; }
    int numCols() const { return cols; }
    Matrix transpose() const;
    Matrix multiply(const Matrix& other) const;
    Matrix inverse() const;
    void qrDecompose(Matrix& Q, Matrix& R) const;
    double determinant() const; // Added determinant method declaration
    void print() const;
};

#endif // MATRIX_HPP

