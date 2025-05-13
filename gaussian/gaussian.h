#ifndef GAUSSIAN_H
#define GAUSSIAN_H
#include <Eigen/Dense>

// Solves Ax = b using custom Gaussian elimination
Eigen::VectorXd solveSystem(const Eigen::MatrixXd& coefficients, const Eigen::VectorXd& constants);

// Generates a random solvable test system A * x = b
void createTestSystem(Eigen::MatrixXd& A, Eigen::VectorXd& b, int size, unsigned seed);

#endif