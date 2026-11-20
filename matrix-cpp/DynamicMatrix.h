#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

// Allocation-free runtime-sized matrix
// Probably unsafe as hell but who cares
class DynamicMatrix
{
public:
	__forceinline explicit DynamicMatrix(size_t rows, size_t columns)
	{
		if (rows > 0 && columns > SIZE_MAX / rows) 
		{
			char message[256];
			snprintf(message, sizeof(message),
				"%dx%d DynamicMatrix capacity overflows size_t", rows, columns);
			throw std::runtime_error(message);
		}
		Rows = rows;
		Columns = columns;
		Capacity = rows * columns;
		Values = (int*)alloca(Capacity * sizeof(int));
		for (int i = 0; i < Capacity; i++)
		{
			Values[i] = 0;
		}
	}

	DynamicMatrix(const DynamicMatrix& original)
	{
		memcpy(this->Values, &original.Values, Capacity * sizeof(int));
	}

	int Rows;
	int Columns;
	size_t Capacity;
	int* Values;

#pragma region Indexing
	constexpr int& At(size_t row, size_t column)
	{
		int index = row * Columns + column;
		if (index > Capacity) std::out_of_range("out of range");
		return Values[index];
	}

	constexpr const int& At(size_t row, size_t column) const
	{
		int index = row * Columns + column;
		if (index > Capacity) throw std::out_of_range("out of range");
		return Values[index];
	}

	constexpr int& operator[](size_t row, size_t column)
	{
		int index = row * Columns + column;
		if (index > Capacity) throw std::out_of_range("out of range");
		return Values[index];
	}

	constexpr const int& operator[](size_t row, size_t column) const
	{
		int index = row * Columns + column;
		if (index > Capacity) throw std::out_of_range("out of range");
		return Values[index];
	}
#pragma endregion

	// Returns the current instance to allow chaining
	DynamicMatrix& Set(size_t row, size_t column, int value)
	{
		this->At(row, column) = value;
		return *this;
	}

	DynamicMatrix Multiply(int scalar) const
	{
		DynamicMatrix result = *this;

		for (int i = 0; i < this->Rows; i++)
		{
			for (int j = 0; j < this->Columns; j++)
			{
				result.At(i, j) *= scalar;
			}
		}
		return result;
	}

	DynamicMatrix operator*(int scalar) const
	{
		return this->Multiply(scalar);
	}

	DynamicMatrix Multiply(const DynamicMatrix& other) const
	{
		if (this->Columns != other.Rows)
		{
			char message[256];
			snprintf(message, sizeof(message),
				"Rows and columns must match (got %dx%d * %dx%d)",
				this->Rows, this->Columns, other.Rows, other.Columns);
			throw std::runtime_error(message);
		}
		DynamicMatrix result(this->Rows, other.Columns);

		for (int i = 0; i < this->Rows; i++)
		{
			for (int j = 0; j < other.Columns; j++)
			{
				int sum = 0;
				for (size_t k = 0; k < other.Columns; k++)
				{
					sum += (*this)[i, k] * other[k, j];
				}
				result.Set(i, j, sum);
			}
		}
		return result;
	}

	DynamicMatrix operator*(const DynamicMatrix& other) const
	{
		return this->Multiply(other);
	}
};