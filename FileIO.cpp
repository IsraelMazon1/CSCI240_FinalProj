#include "FileIO.hpp"
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>

void FileIO::saveState(const std::string& filename, const Matrix& matrix, const std::vector<double>& eigenvalues) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }
    int rows = matrix.numRows();
    int cols = matrix.numCols();
    file << rows << " " << cols << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << matrix.get(i, j) << " ";
        }
        file << eigenvalues[i] << std::endl;
    }
    file.close();
}

std::tuple<Matrix, std::vector<double>> FileIO::loadState(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + filename);
    }
    int rows, cols;
    file >> rows >> cols;
    Matrix matrix(rows, cols);
    std::vector<double> eigenvalues(rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double value;
            file >> value;
            matrix.set(i, j, value);
        }
        file >> eigenvalues[i];
    }
    file.close();
    return std::make_tuple(matrix, eigenvalues);
}

