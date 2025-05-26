#include "gaussian.h"
#include <gtest/gtest.h>

// Test 1: Simple 3x3 system with known solution
TEST(GaussianTest, KnownSolution1) {
    Eigen::MatrixXd A(3, 3);
    Eigen::VectorXd b(3);
    A << 5, 2, -1,
         1, 3, 2,
         2, -1, 4;
    b << 6, 12, 10;

    Eigen::VectorXd x = solveSystem(A, b);

    EXPECT_NEAR(x(0), 0.909091, 1e-5);
    EXPECT_NEAR(x(1), 2.0, 1e-5);
    EXPECT_NEAR(x(2), 2.54545, 1e-5);
}

// Test 2: Identity matrix
TEST(GaussianTest, IdentityMatrix) {
    Eigen::MatrixXd A = Eigen::MatrixXd::Identity(4, 4);
    Eigen::VectorXd b(4);
    b << 7, -3, 2, 0;

    Eigen::VectorXd x = solveSystem(A, b);
    EXPECT_TRUE((x - b).norm() < 1e-6);
}

// Test 3: Singular matrix should throw
TEST(GaussianTest, SingularMatrix) {
    Eigen::MatrixXd A(2, 2);
    Eigen::VectorXd b(2);
    A << 1, 2,
         2, 4;
    b << 5, 10;

    EXPECT_THROW({
        solveSystem(A, b);
    }, std::runtime_error);
}

// Test 4: Zero matrix should throw
TEST(GaussianTest, ZeroMatrix) {
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(2, 2);
    Eigen::VectorXd b(2);
    b << 1, 2;

    EXPECT_THROW({
        solveSystem(A, b);
    }, std::runtime_error);
}

// Test 5: Overdetermined system (4x3) – check least-squares residual
TEST(GaussianTest, OverdeterminedSystem) {
    Eigen::MatrixXd A(4, 3);
    Eigen::VectorXd b(4);
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9,
         10, 11, 12;
    b << 6, 15, 24, 33;

    Eigen::VectorXd x = (A.transpose() * A).ldlt().solve(A.transpose() * b); // Least-squares
    Eigen::VectorXd residual = A * x - b;
    EXPECT_LT(residual.norm(), 1e-4);
}

// Test 6: Underdetermined system (2 equations, 3 unknowns)
TEST(GaussianTest, UnderdeterminedSystem) {
    Eigen::MatrixXd A(2, 3);
    Eigen::VectorXd b(2);
    A << 1, 2, 3,
         4, 5, 6;
    b << 14, 32;

    Eigen::VectorXd x = (A.transpose() * A).ldlt().solve(A.transpose() * b); // Least-squares
    EXPECT_EQ(x.size(), 3);
    EXPECT_LT((A * x - b).norm(), 1e-6);
}

// Test 7: Random 5x5 system
TEST(GaussianTest, Random5x5) {
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(5, 5);
    Eigen::VectorXd b = Eigen::VectorXd::Random(5);
    Eigen::VectorXd x = solveSystem(A, b);
    EXPECT_LT((A * x - b).norm(), 1e-6);
}

// Test 8: Random 10x10 system
TEST(GaussianTest, Random10x10) {
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(10, 10);
    Eigen::VectorXd b = Eigen::VectorXd::Random(10);
    Eigen::VectorXd x = solveSystem(A, b);
    EXPECT_LT((A * x - b).norm(), 1e-6);
}

// Test 9: System with negative coefficients
TEST(GaussianTest, NegativeCoefficients) {
    Eigen::MatrixXd A(3, 3);
    Eigen::VectorXd b(3);
    A << -3, 2, -5,
         -1, 0, 2,
         5, -1, -3;
    b << -1, 3, -4;

    Eigen::VectorXd x = solveSystem(A, b);
    EXPECT_LT((A * x - b).norm(), 1e-6);
}

// Test 10: System with decimal coefficients
TEST(GaussianTest, DecimalCoefficients) {
    Eigen::MatrixXd A(3, 3);
    Eigen::VectorXd b(3);
    A << 1.2, 0.5, -0.7,
         -1.1, 2.3, 1.4,
         0.8, -1.2, 3.3;
    b << 2.4, -1.7, 3.5;

    Eigen::VectorXd x = solveSystem(A, b);
    EXPECT_LT((A * x - b).norm(), 1e-6);
}