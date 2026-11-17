#include <iostream>
#include "matrix.h"


int main()
{
    Matrix<2, 2> matrix{};
    matrix.Set(0, 0, 1).Set(0, 1, 2).Set(1, 0, 3).Set(1, 1, 4);
    for (int i = 0; i < matrix.Rows; i++)
    {
        for (int j = 0; j < matrix.Columns; j++)
        {
            std::cout << matrix[i, j] << '\n';
        }
    }
}