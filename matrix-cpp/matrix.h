#pragma once

#include <array>
#include <cstddef>

template <size_t R, size_t C>
class Matrix
{
public:
	static_assert(C == 0 || R <= SIZE_MAX / C, "Matrix capacity overflows size_t");
	static constexpr int Rows = R;
	static constexpr int Columns = C;
	static constexpr size_t Capacity = R * C;
	std::array<int, Capacity> Values;

	constexpr int& At(size_t row, size_t column)
	{
		return Values[row * C + column];
	}

	constexpr const int& At(size_t row, size_t column) const
	{
		return Values[row * C + column];
	}

	constexpr int& operator[](size_t row, size_t column)
	{
		return Values[row * C + column];
	}

	constexpr const int& operator[](size_t row, size_t column) const
	{
		return Values[row * C + column];
	}

	// Returns the current instance to allow chaining
	Matrix<R, C>& Set(size_t row, size_t column, int value)
	{
		this->At(row, column) = value;
		return *this;
	}

	Matrix<R, C> Multiply(int scalar) const
	{
		Matrix<R, C> result = *this;

		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				result.At(i, j) *= scalar;
			}
		}
		return result;
	}

	Matrix<R, C> operator*(int scalar) const
	{
		return this->Multiply(scalar);
	}

	template<size_t K>
	Matrix<R, K> Multiply(const Matrix<C, K>& other) const
	{
		Matrix<R, K> result{};
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < K; j++)
			{
				int sum = 0;
				for (size_t k = 0; k < C; k++)
				{
					sum += (*this)[i, k] * other[k, j];
				}
				result.Set(i, j, sum);
			}
		}
		return result;
	}

	template<size_t K>
	Matrix<R, K> operator*(const Matrix<C, K>& other) const
	{
		return this->Multiply(other);
	}
};