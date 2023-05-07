#pragma once
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

bool Is_zero(double value);
#define Epsilon 1e-10
#define Full_pivoting


template <typename T>
class Matrix final
    {
    private:
        T** array_;
        int size_;
        
    public:
        Matrix() : size_(0) {}
        Matrix(int size_);
        Matrix (int size, T deter);
        static Matrix unitary(int size);
        static Matrix zero_matrix(int size);
        Matrix(const Matrix &rhs);
        Matrix(Matrix &&rhs);
        Matrix& operator=(const Matrix &rhs);
        Matrix& operator=(Matrix &&rhs);
        Matrix& operator*(Matrix &rhs);
        ~Matrix();
        void Read_matrix(std::istream& in);
        void Print_matrix(std::ostream& out) const;
        T Determinant();
        T LU_determinant();
        int Size() const { return size_; };
        int Gauss_algo();
        T Int_Deter();
        void Decomposition(Matrix* L, Matrix* U, Matrix* P) const;
        void Clear_matrix();
        int Pivoting(int j);
        T* operator[](int x) { return array_[x]; }
        const T* operator[](int x) const { return array_[x]; }
        static Matrix Solve_low_system(Matrix &P, Matrix &L);     //LY = P
        static Matrix Solve_upper_system(Matrix &Y, Matrix &U); //UA^-1 = Y
        static Matrix Reversed_matrix(Matrix &A);
        static Matrix Multiply(const Matrix &lhs, const Matrix &rhs);

    private:
        void Mul_raw(int obj, T value);
        void Div_raw(int obj, T value);
        void Add_another_raw(int obj, int subj, T coefficent);
        void Add_another_colomn(int obj, int subj, T coefficent);
        void Swap_raw(int first, int second);
        void Swap_colomn(int first, int second);

    };

template <typename T>
bool operator ==(const Matrix<T>& lhs, const Matrix<T>& rhs)
    {
    if (lhs.Size() != rhs.Size())
        return false;
    int size = lhs.Size();
    for (int i = 0; i != size; ++i)
        for (int j = 0; j != size; ++j)
            if (!Is_zero(lhs[i][j] - rhs[i][j]))
                return false;
    return true;
    }

template <typename T>
Matrix<T>::Matrix(int size)
    {
    int i = 0;
    try {
        array_ = new T*[size];
        for (i = 0; i < size; ++i)
        array_[i] = new T[size];
    }
    catch(...) {
        for (int j = 0; j < i; j++)
            delete [] array_[j];
        delete [] array_;
        throw;    
    }
    size_ = size;
    }


template <typename T>
Matrix<T>::Matrix(const Matrix &rhs)
    {
    int i = 0;
    try {
    array_ = new T*[rhs.size_];
    for (i = 0; i < rhs.size_; ++i)
        array_[i] = new T[rhs.size_];
    for (i = 0; i != rhs.size_; ++i)
        for (int j = 0; j != rhs.size_; ++j)
            array_[i][j] = rhs.array_[i][j];
    }
    catch(...) {
        for (int j = 0; j < i; j++)
            delete [] array_[j];
        delete [] array_;
        throw;    
    }
    size_ = rhs.size_;
    }

template <typename T>
Matrix<T>::Matrix(Matrix &&rhs)
    {
    if (this != &rhs)
        {
        size_  = rhs.size_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.size_  = 0;
        }
    }


template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix &rhs)
    {
    Matrix matr(rhs);
    std::swap(matr.array_, array_);
    std::swap(matr.size_, size_);
    return *this;
    }


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix &&rhs)
    {
    if (&rhs != this)
        {
        for (int i = 0; i != size_; ++i)
            delete[] array_[i];
        array_ = rhs.array_;
        size_   = rhs.size_;
        rhs.array_ = nullptr;
        rhs.size_  = 0;
        return *this;
        }
    return *this;
    }


template <typename T>
Matrix<T>::~Matrix()
    {
    //std::cout << "Destructor wwas called\n";
    for (int i = 0; i != size_; ++i)
        delete [] array_[i];
    if (size_ > 0)
        delete [] array_;
    }


template <typename T>
Matrix<T> Matrix<T>::Multiply(const Matrix &lhs, const Matrix &rhs)
    {
    //naive matrix multiplication
    if (lhs.Size() != rhs.Size())
        {
        std::cout << "Wrong sizes of multiplied matrixes" << std::endl;
        throw;
        }
    Matrix<T> res(lhs.Size());
    res.Clear_matrix();
    for (int k = 0; k < lhs.Size(); ++k)
        for (int j = 0; j < lhs.Size(); ++j)
            for (int i = 0; i < lhs.Size(); ++i)
                res[k][j] += lhs[k][i] * rhs[i][j];
    return res;
    }


template <typename T>
void Matrix<T>::Print_matrix(std::ostream& out) const 
    {
    for (int i = 0; i != size_; ++i)
        {
        for (int j = 0; j != size_; ++j)
            {
            out.width(10);
            if (fabs(array_[i][j]) < Epsilon)
                out << 0 << " ";
            else 
                out << array_[i][j] << " ";
            }
        out << std::endl;
        }
    out << std::endl;
    }


template <typename T>
void Matrix<T>::Read_matrix(std::istream& in)
    {
    for (int i = 0; i != size_; ++i)
        for (int j = 0; j != size_; ++j)
            in >> array_[i][j];
    }


/// \brief Create upper triangle matrix with random values, but with entered determinant
template <typename T>
Matrix<T>::Matrix(int size, T deter)
    {
    size_ = 0;
    (*this) = Matrix(size);
    srand(time(0));
    for (int i = 0; i != size; ++i)
        {
        for (int j = 0; j!= size; ++j)
            {
            if (i == j)
                array_[i][j] = 1;
            else if (j > i)
                array_[i][j] = rand() % 10;
            else array_[i][j] = 0;
            }
        }
    array_[0][0] = deter;
    for (int i = 1; i != size; i++)
        Add_another_raw(i, 0, rand() % 20);

    for (int i = 0; i != size - 1; i++)
        Add_another_colomn(i, size_ - 1, rand() % 20);
    }


template <typename T>
Matrix<T> Matrix<T>::unitary(int size)
    {
    Matrix<T> matr(size);
    for (int i = 0; i != matr.size_; ++i)
        for (int j = 0; j != matr.size_; ++j)
            {
            if (i == j)
                matr.array_[i][j] = 1;
            else 
                matr.array_[i][j] = 0;
            }
    return matr;
    }


template <typename T>
Matrix<T> Matrix<T>::zero_matrix(int size)
    {
    Matrix<T> matr(size);
    for (int i = 0; i != matr.size_; ++i)
        for (int j = 0; j != matr.size_; ++j)
            matr.array_[i][j] = 0;
    return matr;
    }


template <typename T>
Matrix<T> Matrix<T>::Solve_low_system(Matrix<T> &P, Matrix<T> &L)
    {
    Matrix<T> Y(L.Size());
    if (L.Size() != P.Size()) {
        std::cout << "wrong size of b" << std::endl;
        return Y;
    }
        
    for (int k = 0; k < L.Size(); ++k)
        {
        for (int i = 0; i < L.Size(); ++i)
            {
            Y[i][k] = P[i][k];
            for (int j = 0; j < i; ++j)
                Y[i][k] -= L[i][j] * Y[j][k];
            Y[i][k] /= L[i][i];
            }
        }
    return Y;
    }


template <typename T>
Matrix<T>  Matrix<T>::Solve_upper_system(Matrix<T> &Y, Matrix<T> &U)
    {
    Matrix<T> A_inv(U.Size());
    if (U.Size()!= Y.Size()) {
        std::cout << "wrong size of b" << std::endl;
        return A_inv;
    }
        
    for (int k = 0; k < U.Size(); ++k)
        {
        for (int i = U.Size() - 1; i >= 0; --i)
            {
            A_inv[i][k] = Y[i][k];
            for (int j = U.Size() - 1; j > i; --j)
                A_inv[i][k] -= U[i][j] * A_inv[j][k];
            A_inv[i][k] /= U[i][i];
            }
        }
    return A_inv;
    }


template <typename T>
Matrix<T>  Matrix<T>::Reversed_matrix(Matrix<T> &A) 
    {
    Matrix<T> L(A.Size()), U(A);
    Matrix<T> P = unitary(A.Size());
    A.Decomposition(&L, &U, &P);
    Matrix<T> Y = Solve_low_system(P, L);
    Matrix<T> A_inv = Solve_upper_system(Y, U);
    return A_inv;
    }


template <typename T>
void Matrix<T>::Mul_raw(int obj, T value)
    {
    if (obj >= size_ || obj < 0)
        {
        std::cout << "Mul_raw: incorrect input, no such raw " << obj << std::endl;
        return;
        }
    for (int j = 0; j != size_; ++j)
        array_[obj][j] *= value;
    }


template <typename T>
void Matrix<T>::Div_raw(int obj, T value)
    {
    if (obj >= size_ || obj < 0)
        {
        std::cout << "Mul_raw: incorrect input, no such raw " << obj << std::endl;
        return;
        }
    for (int j = 0; j != size_; ++j)
        array_[obj][j] /= value;
    }


template <typename T>
void Matrix<T>::Add_another_raw(int obj, int subj, T coefficent)
    {
    if (obj >= size_ || obj < 0 || subj >= size_ || subj < 0)
        {
        std::cout << "Add_another_raw: incorrect input, no such raw" << std::endl;
        return;
        }
    for (int j = 0; j != size_; ++j)
        array_[obj][j] += array_[subj][j] * coefficent;
    }


template <typename T>
void Matrix<T>::Add_another_colomn(int obj, int subj, T coefficent)
    {
    if (obj >= size_ || obj < 0 || subj >= size_ || subj < 0)
        {
        std::cout << "Add_another_raw: incorrect input, no such raw" << std::endl;
        return;
        }
    for (int j = 0; j != size_; ++j)
        array_[j][obj] += array_[j][subj] * coefficent;
    }


template <typename T>
int Matrix<T>::Pivoting(int j)
    {
    int n_max = j, k_max = j, number_of_reversing = 0; // j shows with which submatrix we work
    for (int n = j; n < size_; ++n)
        for (int k = j; k < size_; ++k)
            {
            if (fabs(array_[n][k]) - fabs(array_[n_max][k_max]) > Epsilon)
                {
                n_max = n;
                k_max = k;
                }
            }
    
    Swap_raw(j, n_max);
    Swap_colomn(j, k_max);

    if (j == k_max)           //Count the number of uncompensated reversings
        number_of_reversing++;
    if (j == n_max)
        number_of_reversing++;
    return number_of_reversing;
    }


template <typename T>
int Matrix<T>::Gauss_algo()
    {
    int number_of_reversing = 0;
    for (int j = 0; j != size_; ++j) //Find the max element end trasport it to diagonale, (full pivoting)
        {
        #ifdef Full_pivoting
        number_of_reversing += Pivoting(j);
        #endif

        for (int i = j + 1; i != size_; ++i)
            {
            if (Is_zero(array_[j][j]))
                {
                printf("zero_matrix\n");
                return 0;
                }
            Add_another_raw(i, j, -array_[i][j] / array_[j][j]);
            }
        }
    return number_of_reversing;
    }

template <typename T>
T Matrix<T>::Int_Deter()
    {
    Print_matrix(std::cout);
    Matrix matr(*this);
    double multiplier = 1;
    T deter = 1;
    for (int j = 0; j != size_; ++j)
        {
        for (int i = j + 1; i != size_; ++i)
            {
            if (Is_zero(array_[j][j]))
                {
                printf("zero_matrix\n");
                return 0;
                }
            T k1 = matr.array_[i][j], k2 = matr.array_[j][j];
            if (k1 != 0) 
                {
                matr.Mul_raw(i, k2);
                matr.Mul_raw(j, k1);
                matr.Add_another_raw(i, j, -1);
                matr.Div_raw(j, k1);
                multiplier *= k2;
                }
            }
        }
    for (int i = 0; i < matr.size_; i++)
        deter *= matr.array_[i][i];
    std::cout << "deter = " << deter << " multiplier = " << multiplier << std::endl;
    return deter / multiplier;
    }

template <typename T>
void Matrix<T>::Swap_raw(int first, int second)
    {
    if (first >= size_ || second >= size_ || first < 0 || second < 0)
        std::cout << "Invalid input in Swap_raw, there's no such index in Matrix" << std::endl;
    T* temp = array_[first];
    array_[first]  = array_[second];
    array_[second] = temp;
    }


template <typename T>
void Matrix<T>::Swap_colomn(int first, int second)
    {
    if (first >= size_ || second >= size_ || first < 0 || second < 0)
        std::cout << "Invalid input in Swap_colomn, there's no such index in Matrix" << std::endl;
    for (int i = 0; i != size_; ++i)
        {
        T temp = array_[i][first];
        array_[i][first] = array_[i][second];
        array_[i][second] = temp;
        }
    }


template <typename T>
T Matrix<T>::Determinant()
    {
    T deter = 1;
    Matrix matr(*this);
    int Is_minus = matr.Gauss_algo() % 2;
    for (int i = 0; i != size_; ++i)
        {
        deter *= matr.array_[i][i];
        //std::cout << "deter = " << deter << std::endl;
        }

    if (Is_minus)
        return -deter;
    else
        return deter;
    }


bool Is_zero(double value)
    {
    if (-Epsilon < value && value < Epsilon)
        return 1;
    else 
        {
        //std::cout << "value = " << value << '\n';
        return 0;
        }
    } 


template <typename T>
void Matrix<T>::Clear_matrix()
    {
    for (int i = 0; i != size_; ++i)
        for (int j = 0; j != size_; ++j)
            array_[i][j] = 0;
    }
    

template <typename T>
void Matrix<T>::Decomposition(Matrix<T>* L, Matrix<T>* U, Matrix<T>* P) const
    { 
    L -> Clear_matrix();
    
	for(int i = 0; i < size_; i++)
		for(int j = i; j < size_; j++)
            {
            if (Is_zero(U -> array_[i][i]))
                {
                std::cout << "Cant use this algo, because, some of main minors are degenerate\n";
                throw;
                }

			L -> array_[j][i] = U -> array_[j][i] / U -> array_[i][i];
            }
	
	for(int k = 1; k < size_; k++)
        {
        int max_str_index = k - 1;
        for (int l = k - 1; l < size_; l++) {
            //std::cout << U -> array_[l][k - 1] << "vs" << U -> array_[max_str_index][k - 1] << std::endl;
            if ((fabs(U -> array_[l][k - 1]) - fabs(U -> array_[max_str_index][k - 1])) > Epsilon)
                max_str_index = l;
        U -> Swap_raw(k - 1, max_str_index);
        P -> Swap_raw(k - 1, max_str_index);
        }
            
        for(int i = k-1; i < size_; i++)
            for(int j = i; j < size_; j++)
                L -> array_[j][i] = U -> array_[j][i] / U -> array_[i][i];

        for(int i = k; i < size_; i++)
            for(int j = k-1; j < size_; j++)
                U -> array_[i][j] = U -> array_[i][j] - L -> array_[i][k-1] * U -> array_[k-1][j];
        }
     
    }


template <typename T>
T Matrix<T>::LU_determinant()
    {
    Matrix<T> L(size_), U(*this);
    Matrix<T> P = unitary(size_);
    P.Print_matrix(std::cout);
    Decomposition(&L, &U, &P);
    T deter = 1;
    P.Print_matrix(std::cout);
    
    for (int i = 0; i < size_; i++)
        deter *= L.array_[i][i] * U.array_[i][i];
    return deter;
    }

