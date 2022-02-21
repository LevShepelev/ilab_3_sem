
void Matrix::Read_matrix()
    {
    int N = 0;
    std::cin >> N;
    for (int i = 0; i != N, ++i)
        for (int j = 0; j != N; ++j)
            std::cin >> (array_ + i * size)[j];
    }