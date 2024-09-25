#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include "EigenCalculator.hpp"
#include "FileIO.hpp"

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows and columns of the matrix (type two numbers with a space in between, like so: 3 3): ";
    std::cin >> rows >> cols;

    Matrix matrix(rows, cols);
    std::cout << "Enter the elements of the matrix row by row separated by spaces:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double value;
            std::cin >> value;
            matrix.set(i, j, value);
        }
    }

    std::cout << "Matrix after initialization:\n";
    matrix.print();

    std::vector<double> eigenvalues; // Initialize vector for eigenvalues
    char compute;
    std::cout << "Do you want to compute the eigenvalues? (y/n): ";
    std::cin >> compute;
    if (compute == 'y' || compute == 'Y') {
        try {
            eigenvalues = EigenCalculator::computeEigenvalues(matrix);
            std::cout << "Eigenvalues: ";
            for (size_t i = 0; i < eigenvalues.size(); ++i) {
                std::cout << eigenvalues[i];
                if (i != eigenvalues.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Failed to compute eigenvalues: " << e.what() << std::endl;
        }
    }

    double det = matrix.determinant();
    std::cout << "The matrix is " << (det != 0.0 ? "invertible" : "not invertible") << " because its determinant is " << det << ".\n";

    std::cout << "Do you want to compute the inverse of the matrix? (y/n): ";
    std::cin >> compute;
    if (compute == 'y' || compute == 'Y') {
        try {
            Matrix inverseMatrix = matrix.inverse();
            std::cout << "Inverse of the matrix:\n";
            inverseMatrix.print();
        } catch (const std::exception& e) {
            std::cerr << "Error computing inverse: " << e.what() << std::endl;
        }
    }

    // Saving the state of the matrix and eigenvalues to a file
    std::string filename = "matrix_state.txt";
    FileIO::saveState(filename, matrix, eigenvalues);

    // Optionally, load the state back from the file
    std::cout << "Load saved state from file? (y/n): ";
    std::cin >> compute;
    if (compute == 'y' || compute == 'Y') {
        auto loaded = FileIO::loadState(filename);
        Matrix loadedMatrix = std::get<0>(loaded);
        std::vector<double> loadedEigenvalues = std::get<1>(loaded);

        std::cout << "Loaded Matrix:\n";
        loadedMatrix.print();
        std::cout << "Loaded Eigenvalues: ";
        for (auto ev : loadedEigenvalues) {
            std::cout << ev << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

