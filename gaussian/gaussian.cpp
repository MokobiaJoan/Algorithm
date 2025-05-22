#include "gaussian.h"
#include <stdexcept>
#include <cmath>
#include <random>

Eigen::VectorXd solveSystem(const Eigen::MatrixXd& coefficients, const Eigen::VectorXd& constants) {
    const int n = coefficients.rows();
    Eigen::MatrixXd aug(n, n + 1);
    aug << coefficients, constants;


    for (int col = 0; col < n; ++col) {
        int pivot = col;
        for (int row = col + 1; row < n; ++row) {
            if (std::abs(aug(row, col)) > std::abs(aug(pivot, col)))
                pivot = row;
        }

        if (std::abs(aug(pivot, col)) < 1e-10)
            throw std::runtime_error("Matrix is singular or nearly singular");

        aug.row(col).swap(aug.row(pivot));

        for (int row = col + 1; row < n; ++row) {
            double factor = aug(row, col) / aug(col, col);
            aug.row(row) -= factor * aug.row(col);
        }
    }

    Eigen::VectorXd result(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = aug(i, n);
        for (int j = i + 1; j < n; ++j) {
            sum -= aug(i, j) * result(j);
        }
        result(i) = sum / aug(i, i);
    }    

    return result;
}

void createTestSystem(Eigen::MatrixXd& A, Eigen::VectorXd& b, int size, unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<> dist(-10.0, 10.0);

    Eigen::VectorXd x_true(size);
    A.resize(size, size);
    b.resize(size);

    for (int i = 0; i < size; ++i) {
        x_true(i) = dist(rng);
        for (int j = 0; j < size; ++j) {
            A(i, j) = dist(rng);
        }
    }

    b = A * x_true;
}