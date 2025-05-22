#include "gaussian.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool loadMatrixFromCSV(const std::string& filename, Eigen::MatrixXd& A, Eigen::VectorXd& b) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::vector<std::vector<double>> rows;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string entry;
        std::vector<double> row;

        while (std::getline(ss, entry, ','))
            row.push_back(std::stod(entry));

        rows.push_back(row);
    }

    int n = rows.size();
    if (n == 0 || rows[0].size() < 2) return false;

    A.resize(n, rows[0].size() - 1);
    b.resize(n);

    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < rows[i].size() - 1; ++j)
            A(i, j) = rows[i][j];
        b(i) = rows[i].back();
    }

    return true;
}

int main() {
    const std::string filename = "input.csv";

    Eigen::MatrixXd A;
    Eigen::VectorXd b;

    if (!loadMatrixFromCSV(filename, A, b)) {
        std::cerr << "Failed to load matrix from file: " << filename << "\n";
        return 1;
    }

    try {
        Eigen::VectorXd x = solveSystem(A, b);

       std::ofstream outFile("output.csv");
if (outFile.is_open()) {
    for (int i = 0; i < x.size(); ++i) {
        outFile << x(i) << "\n";
    }
    std::cout << "Computation completed, view result in output.csv" << std::endl;
} else {
    std::cerr << "Error: Could not open output.csv for writing.\n";
}
    } catch (const std::exception& e) {
        std::cerr << "Solver error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}