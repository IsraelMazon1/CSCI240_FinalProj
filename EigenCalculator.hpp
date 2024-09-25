#ifndef EIGEN_CALCULATOR_HPP
#define EIGEN_CALCULATOR_HPP

#include "Matrix.hpp"
#include <vector>

class EigenCalculator {
public:
    static std::vector<double> computeEigenvalues(const Matrix& matrix);
};

#endif // EIGEN_CALCULATOR_HPP

