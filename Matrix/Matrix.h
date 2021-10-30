#include <iostream>
#include <cstring>


template <typename T>
class Matrix
    {
    private:
        T** array_;
        int size_;
    public:
        Matrix() : size_(0) {}
        Matrix(int size_);
        Matrix(const Matrix &rhs);
        Matrix(Matrix &&rhs);
        Matrix& operator=(const Matrix &rhs);
        Matrix& operator=(Matrix &&rhs);
        ~Matrix();
        void Read_matrix();
        void Print_matrix() const;
        T Determinant();
        int Size() const { return size_; };
    private:
        void Mul_string(int obj, T value);
        void Add_another_string(int obj, int subj, T coefficent);
        void Gauss_algo();
        void Swap_strings(int first, int second);
    };

template <typename T>
Matrix<T>::Matrix(int size)
    {
    size_ = size;
    array_ = new T*[size];
    for (int i = 0; i < size; ++i)
        array_[i] = new T[size];
    }


template <typename T>
Matrix<T>::Matrix(const Matrix &rhs)
    {
    size_ = rhs.size_;
    array_ = new T*[size_];
    for (int i = 0; i < size_; ++i)
        array_[i] = new T[size_];
    for (int i = 0; i != size_; ++i)
        for (int j = 0; j != size_; ++j)
            array_[i][j] = rhs.array_[i][j];
    }


template <typename T>
Matrix<T>::Matrix(Matrix &&rhs)
    {
    if (this != &rhs)
        {
        delete[] array_;
        size_  = rhs.size_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.size_  = 0;
        }
    }


template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix &rhs)
    {
    this -> array_ = rhs.array_;
    this -> size_  = rhs.size_;
    return *this;
    }


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix &&rhs)
    {
    if (&rhs != this)
        {
        delete[] array_;
        this -> array_ = rhs.array_;
        this -> size   = rhs.size_;
        rhs.array_ = nullptr;
        rhs.size_  = 0;
        return *this;
        }
    }


template <typename T>
Matrix<T>::~Matrix()
    {
    array_ = 0;
    free(array_);
    }


template <typename T>
void Matrix<T>::Print_matrix() const 
    {
    for (int i = 0; i != size_; ++i)
        {
        for (int j = 0; j != size_; ++j)
            {
            std::cout.width(3);
            std::cout << array_[i][j] << " ";
            }
        std::cout << std::endl;
        }
    }


template <typename T>
void Matrix<T>::Read_matrix()
    {
    for (int i = 0; i != size_; ++i)
        for (int j = 0; j != size_; ++j)
            std::cin >> array_[i][j];
    }

template <typename T>
void Matrix<T>::Mul_string(int obj, T value)
    {
    for (int j = 0; j != size_; ++j)
        array_[obj][j] *= value;
    }


template <typename T>
void Matrix<T>::Add_another_string(int obj, int subj, T coefficent)
    {
    for (int j = 0; j != size_; ++j)
        array_[obj][j] += array_[subj][j] * coefficent;
    }


template <typename T>
void Matrix<T>::Gauss_algo()
    {
    for (int j = 0; j != size_; ++j)
        for (int i = j + 1; i != size_; ++i)
            {
            if (array_[j][j] != 0)
                {
                //printf("i = %d, j = %d, array[%d][%d] = %lg, array[%d][%d] = %lg\n", i, j, i, j, -array_[i][j], j, j, array_[j][j]);
                Add_another_string(i, j, -array_[i][j] / array_[j][j]);
                }
            else Swap_strings(i, j);
            }
    }


template <typename T>
void Matrix<T>::Swap_strings(int first, int second)
    {
    if (first >= size_ || second >= size_ || first < 0 || second < 0)
        std::cout << "Invalid input in Swap_strings, there's no such index in Matrix" << std::endl;
    T* temp = array_[first];
    array_[first]  = array_[second];
    array_[second] = temp;
    }


template <typename T>
T Matrix<T>::Determinant()
    {
    T deter = array_[0][0];
    Matrix matr(*this);
    matr.Gauss_algo();
    for (int i = 1; i != size_; ++i)
        deter *= matr.array_[i][i];
    return deter;
    }


