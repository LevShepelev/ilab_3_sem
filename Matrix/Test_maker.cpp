#include <fstream>
#include <iostream>
#include <ctime>
#include "Matrix.h"


int main()
    {
    int size = 25;
    double deter = 10;
    std::ofstream fout_1("Test_1.txt");
    Matrix<double> matr(size, deter);
    Matrix<double> matr_1(matr);
    matr.Print_matrix(fout_1);
    std::cout << matr.LU_determinant() << " another " << matr_1.Determinant() << std::endl;
    }
