#include "../include/Matrix.h"

int main() {
    int N = 0;
    std::cin >> N;
    Matrix<double> matrix(N);
    matrix.Read_matrix(std::cin);
    Matrix<double> L(matrix.Size()), U(matrix);
    Matrix<double> P = Matrix<double>::unitary(matrix.Size());
    
    matrix.Decomposition(&L, &U, &P);
    std::cout << "L" << std::endl;
    L.Print_matrix(std::cout);
    std::cout << "U" << std::endl;
    U.Print_matrix(std::cout);

    std::cout << "A_inversed" << std::endl;
    Matrix<double> matrix_inv = Matrix<double>::Reversed_matrix(matrix);
    matrix.Print_matrix(std::cout);
    std::cout << "A_inversed * A" <<std::endl;
    Matrix<double> check = Matrix<double>::Multiply(matrix, matrix_inv);
    check.Print_matrix(std::cout);
    }