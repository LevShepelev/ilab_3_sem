#include "../include/Matrix.h"

int main()
    {
    int N = 0;
    std::cin >> N;
    Matrix<double> matrix(N);
    matrix.Read_matrix();
    double deter = matrix.Determinant();
    std::cout << deter << std::endl;
    }