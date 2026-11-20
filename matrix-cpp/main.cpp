#include <iostream>
#include "matrix.h"
#include "DynamicMatrix.h"

int main()
{
    Matrix<2, 2> matrix{};
    matrix.Set(0, 0, 1).Set(0, 1, 2).Set(1, 0, 3).Set(1, 1, 4);
    std::cout << matrix;

    DynamicMatrix dynamic(2, 2);
    dynamic.Set(0, 0, 1).Set(0, 1, 2).Set(1, 0, 3).Set(1, 1, 4);
    std::cout << dynamic;

    DynamicMatrix copy = dynamic;
    std::cout << copy;

    DynamicMatrix* heap = new DynamicMatrix(2, 2);
    std::cout << *heap;
}