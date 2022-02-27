#include <gtest/gtest.h>
#include <iostream>
#include "../include/Matrix.h"

TEST(Matrix, Destructor) {
    const int count = 10;
    Matrix<int> matr(count);
}

TEST(Matrix, Copy_constructor) {
    const int deter = 1, count = 2;
    Matrix<double>* matr_ptr = new Matrix<double>(count, deter);
    Matrix<double> matr_copy(*matr_ptr);
    delete matr_ptr;
    ASSERT_EQ(Is_zero(matr_copy.Determinant() - deter), true);
}

TEST(Matrix, Move_constructor) {
    const int deter = 1, count = 2;
    Matrix<double>* matr = new Matrix<double>(count, deter);
    Matrix<double>* matr_copy = new Matrix<double>(Matrix<double>(*matr));
    delete matr;
    ASSERT_EQ(Is_zero(matr_copy -> Determinant() - deter), true);
    delete matr_copy;
}

TEST(Matrix, Copy_assigment) {
    const int deter = 1, count = 2;
    Matrix<double>* matr = new Matrix<double>(count, deter);
    Matrix<double> matr_copy = *matr;
    delete matr;
    ASSERT_EQ(Is_zero(matr_copy.Determinant() - deter), true);

}

TEST(Matrix, Move_assigment) {
    const int deter = 1, count = 3;
    Matrix<double>* matr = new Matrix<double>(count, deter);
    Matrix<double> matr_copy = Matrix<double>(*matr);
    delete matr;
    ASSERT_EQ(Is_zero(matr_copy.Determinant() - deter), true);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}