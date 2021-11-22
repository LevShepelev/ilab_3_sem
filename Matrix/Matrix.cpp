#include "Matrix.h"

int main()
    {
    int N = 0;
    std::cin >> N;
    Matrix<int> matrix(N);
    matrix.Read_matrix();
    int deter =  matrix.Int_Deter();
    std::cout << deter << std::endl;
    }