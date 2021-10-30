#include "Matrix.h"

int main()
    {
    int N = 0;
    std::cin >> N;
    Matrix<double> matrix(N);
    matrix.Read_matrix();
    matrix.Print_matrix();
    std::cout << matrix.Determinant() << std::endl;
    matrix.Print_matrix();
    }