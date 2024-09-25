#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include "Matrix.hpp"
#include <vector>
#include <string>
#include <tuple>

class FileIO {
public:
    static void saveState(const std::string& filename, const Matrix& matrix, const std::vector<double>& eigenvalues);
    static std::tuple<Matrix, std::vector<double>> loadState(const std::string& filename);
};

#endif // FILE_IO_HPP
