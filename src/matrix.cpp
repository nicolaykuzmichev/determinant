#include "matrix.h"

Matrix::Matrix(int _dimension_x, int _dimension_y)
{
	lock_matrix = 1;
	lock_determinant = 1;
	
	dimension_x = 0;
	dimension_y = 0;

	swap_counter = 0;

	if (_dimension_x > 0 & _dimension_y > 0)
	{   
		dimension_x = _dimension_x;
		dimension_y = _dimension_y;

        lock_matrix = 0;

		if (_dimension_x == _dimension_y)
		{
			lock_determinant = 0;
		}

		array_matrix = new long double[_dimension_x * _dimension_y];
		reset_matrix();
	}
}

Matrix::Matrix(const Matrix &_matrix)
{
	lock_matrix = 1;
	lock_determinant = 1;

	dimension_x = 0;
	dimension_y = 0;
	
	swap_counter = 0;

	if (_matrix.dimension_x > 0 & _matrix.dimension_y > 0)
	{   
		lock_matrix = 0;

		if (_matrix.dimension_x == _matrix.dimension_y)
		{
			lock_determinant = 0;
		}
		
		dimension_x = _matrix.dimension_x;
		dimension_y = _matrix.dimension_y;

		array_matrix = new long double[dimension_x * dimension_y];
		reset_matrix();

		for (int loop_row = 0; loop_row < dimension_x; loop_row++)
		{
			for (int loop_column = 0; loop_column < dimension_y; loop_column++)
			{
				set_value(loop_row, loop_column, _matrix.get_value(loop_row, loop_column));
			}
		}
	}
}

long double Matrix::set_value(int _row, int _column, long double _value)
{
	if (lock_matrix == 0 & _row < dimension_x & _column < dimension_y)
	{
		int index = (_row * dimension_y) + (_column);
		array_matrix[index] = _value;
		return 0.0;
	}
	else
	{
		return -1.0;
	}
}

long double Matrix::get_value(int _row, int _column) const
{
	if (lock_matrix == 0 & _row < dimension_x & _column < dimension_y)
	{
		int index = (_row * dimension_y) + (_column);
		return array_matrix[index];
	}
	else
	{
		return 0.0;
	}
}

int Matrix::get_dimension_x() const
{
	return dimension_x;
}

int Matrix::get_dimension_y() const
{
	return dimension_y;
}

int Matrix::get_swap_count() const
{
	return swap_counter;
}

int Matrix::get_lock_matrix() const
{
	return lock_matrix;
}

int Matrix::get_lock_determinant() const
{
	return lock_determinant;
}

long double Matrix::count_determinant_matrix(int method)
{
	if (lock_determinant == 0)
	{
		long double result = 0.0;

		if (dimension_x == 1)
	    {
			return result = get_value(0, 0);
	    }

		if (method == 0)
		{
			Matrix array_triangle_matrix(dimension_x, dimension_y);
			array_triangle_matrix = method_Gauss_counter();
	
			result = 1.0;

			for (int loop = 0; loop < dimension_x; loop++)
			{
				result *= array_triangle_matrix.get_value(loop, loop);
			}

			if (array_triangle_matrix.get_swap_count() % 2 == 1)
			{
				result *= -1.0;
			}

			array_triangle_matrix.~Matrix();

			return result;
		}

		if (method == 1)
		{
			long double **array_of_minors = new long double*[dimension_x - 1];
	
			for (int loop = dimension_x; loop > 1; loop--)
			{
				array_of_minors[dimension_x - loop] = new long double[loop * loop];
			}

			for (int loop = 0; loop < dimension_x * dimension_x; loop++)
			{
				array_of_minors[0][loop] = array_matrix[loop];
			}

			if (dimension_x % 2 == 1)
			{
				result = (-1.0) * method_algebraic_additions_counter(array_of_minors, dimension_x);
			}
			else
			{
				result = method_algebraic_additions_counter(array_of_minors, dimension_x);
			}

			for (int loop = dimension_x; loop > 1; loop--)
			{
				delete [] array_of_minors[dimension_x - loop];
			}

			delete [] array_of_minors;
		}
		return result;
	}
	else
	{
		return 0.0;
	}
}

long double Matrix::method_algebraic_additions_counter(long double **_array_of_minors, int _dimension)
{
	if (lock_determinant == 0)
	{
		if (_dimension == 2)
		{
			return (_array_of_minors[dimension_x - 2][0] * _array_of_minors[dimension_x - 2][3]) -
				   (_array_of_minors[dimension_x - 2][1] * _array_of_minors[dimension_x - 2][2]);
		}
		if (_dimension > 2)
		{
			long double result = 0.0;
			long long int index = 0;
	
			for (int loop = 0; loop < _dimension; loop++)
			{
				index = 0;
	
				for (int loop_row = 1; loop_row < _dimension; loop_row++)
				{
				  for (int loop_column = 0; loop_column < _dimension; loop_column++)
					{
						if (loop != loop_column)
						{
							_array_of_minors[dimension_x - _dimension + 1][index] = 
							_array_of_minors[dimension_x - _dimension][(loop_row * _dimension) + (loop_column)];
	
							index++;
						}
					}
				}
	
				if (_array_of_minors[dimension_x - _dimension][loop] != 0.0)
				{
					if ((loop + 1) % 2 == 1)
					{
						result += (-1.0) * _array_of_minors[dimension_x - _dimension][loop] * 
							    method_algebraic_additions_counter(_array_of_minors, (_dimension - 1));
					}
					if ((loop + 1) % 2 == 0)
					{
						result += _array_of_minors[dimension_x - _dimension][loop] * 
						     method_algebraic_additions_counter(_array_of_minors, (_dimension - 1));
					}
				}
			}
			return result;
		}
	}
	else
	{
		return 0.0;
	}
}

Matrix Matrix::method_Gauss_counter()
{
	Matrix array_matrix(get_dimension_x(), get_dimension_y());
	array_matrix = *this;
	array_matrix.swap_counter = 0;
	
	if (lock_determinant == 0)
	{
		for (int loop_diagonal = 0; loop_diagonal < dimension_x - 1; loop_diagonal++)
		{
			int lock_find = 0;
	
			for (int loop_divider_index = loop_diagonal; loop_divider_index < dimension_x; loop_divider_index++)
			{
			  if (lock_find == 0)
			  {
				if (array_matrix.get_value(loop_diagonal, loop_diagonal) != 0)
				{
					for (int loop_column = loop_diagonal + 1; loop_column < dimension_x; loop_column++) 
					{
						if (array_matrix.get_value(loop_column, loop_diagonal) != 0) 
						{
						    long double divider = array_matrix.get_value(loop_column, loop_diagonal) / array_matrix.get_value(loop_diagonal, loop_diagonal);
	
							for (int loop_row = loop_diagonal; loop_row < dimension_x; loop_row++)
							{
								array_matrix.set_value(loop_column, loop_row, array_matrix.get_value(loop_column, loop_row) - array_matrix.get_value(loop_diagonal, loop_row) * divider);
							}
						}
					}
				lock_find = 1;
				}
				else
				{
					if (loop_diagonal != loop_divider_index)
					{
						array_matrix.swap_rows(loop_diagonal, loop_divider_index);
					}
				}
			  }
			}
		}
		return array_matrix;
	}
	else
	{
		return *this;
	}
}

int Matrix::swap_rows(int _first_row_index, int _second_row_index)
{
	if (lock_matrix == 0  & _first_row_index >= 0 & _second_row_index >= 0 & _first_row_index < dimension_x & _second_row_index < dimension_x)
	{
		if (_first_row_index != _second_row_index)
		{
			for (int loop = 0; loop < get_dimension_y(); loop++)
			{
				long double buff = get_value(_first_row_index, loop);
				set_value(_first_row_index, loop, get_value(_second_row_index, loop));
				set_value(_second_row_index, loop, buff);
			}
			swap_counter++;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int Matrix::swap_columns(int _first_column_index, int _second_column_index)
{
	if (lock_matrix == 0 & _first_column_index >= 0 & _second_column_index >= 0 & _first_column_index < dimension_y & _second_column_index < dimension_y)
	{
		if (_first_column_index != _second_column_index)
		{
			for (int loop = 0; loop < get_dimension_x(); loop++)
			{
				long double buff = get_value(loop, _first_column_index);
				set_value(loop, _first_column_index, get_value(loop, _second_column_index));
				set_value(loop, _second_column_index, buff);
			}
			swap_counter++;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int Matrix::reset_matrix()
{
	if (lock_matrix == 0)
	{
		for (int loop_row = 0; loop_row < dimension_x; loop_row++)
		{
			for (int loop_column = 0; loop_column < dimension_y; loop_column++)
			{
				set_value(loop_row, loop_column, 0.0);
			}
		}
		return 0;
	}
	else
	{
		return -1;
	}
}


Matrix Matrix::inverse_matrix()
{
	if (lock_determinant == 0 & count_determinant_matrix(0) != 0 & get_dimension_x() > 1)
	{
		long double determinant = count_determinant_matrix(0);

		Matrix minor((dimension_x - 1), (dimension_y - 1));
		Matrix inverse_matrix(dimension_x, dimension_y);

		long int index = 0;

		for (int loop_row_keep = 0; loop_row_keep < dimension_x; loop_row_keep++)
		{
			for (int loop_column_keep = 0; loop_column_keep < dimension_y; loop_column_keep++)
			{
				index = 0;

				for (int loop_row = 0; loop_row < dimension_x; loop_row++)
				{
					for (int loop_column = 0; loop_column < dimension_y; loop_column++)
					{
						if (loop_row_keep != loop_row & loop_column_keep != loop_column)
						{
							minor.set_value(int((index - (index % minor.get_dimension_y())) / minor.get_dimension_y()), index % (minor.get_dimension_y()), get_value(loop_row, loop_column));
							index++;
						}
					}
				}
				if ( (loop_row_keep + loop_column_keep) % 2 == 1)
				{
					inverse_matrix.set_value(loop_row_keep, loop_column_keep, ((-1.0) * minor.count_determinant_matrix(0)) / determinant);
				}
				if ( (loop_row_keep + loop_column_keep) % 2 == 0)
				{
					inverse_matrix.set_value(loop_row_keep, loop_column_keep, minor.count_determinant_matrix(0) / determinant);
				}
			}
		}
		return inverse_matrix.transpose_matrix();
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::transpose_matrix() const
{
	if (lock_matrix == 0)
	{
		Matrix transpose_matrix(dimension_y, dimension_x);

		for (int loop_row = 0; loop_row < dimension_x; loop_row++)
		{
			for (int loop_column = 0; loop_column < dimension_y; loop_column++)
			{
				transpose_matrix.set_value(loop_column, loop_row, get_value(loop_row, loop_column));
			}
		}
		return transpose_matrix;
	}
	else
	{
		return *this;
	}
}

long double Matrix::trace_matrix() const
{
	if (lock_determinant == 0)
	{
		long double result = 0.0;

		for (int loop_diagonal = 0; loop_diagonal < dimension_y; loop_diagonal++)
		{
			result += get_value(loop_diagonal, loop_diagonal);
		}
		return result;
	}
	else
	{
		return 0.0;
	}
}

int Matrix::rank_matrix()
{
	if (lock_matrix == 0)
	{
		Matrix array_matrix(dimension_x, dimension_y);
		array_matrix = method_Gauss_counter();

		int rank = 0;

		for (int loop_diagonal = 0; loop_diagonal < dimension_y; loop_diagonal++)
		{
			if (array_matrix.get_value(loop_diagonal,loop_diagonal) != 0)
			{
				rank++;
			}
		}
		return rank;
	}
	else
	{
		return 0;
	}
}

Matrix Matrix::multiplication_matrix(Matrix &_matrix) const
{
	if (lock_matrix == 0 & get_dimension_x() == _matrix.get_dimension_y())
	{
		Matrix _multiplication_matrix(dimension_y, _matrix.get_dimension_x());

		long double sum = 0.0;
		
		for (int loop_row = 0; loop_row < _multiplication_matrix.get_dimension_x(); loop_row++)
		{
			for (int loop_column = 0; loop_column < _multiplication_matrix.get_dimension_y(); loop_column++)
			{
				sum = 0.0;

				for (int loop_line = 0; loop_line < get_dimension_x(); loop_line++)
				{
					sum += get_value(loop_row, loop_line) * _matrix.get_value(loop_line, loop_column);
				}
				_multiplication_matrix.set_value(loop_row, loop_column, sum);
			}
		}
		return _multiplication_matrix;
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::multiplication_matrix_on_number(long double _number) const
{
	if (lock_matrix == 0)
	{
		Matrix multiplication_number_matrix(dimension_x, dimension_y);

		for (int loop_x = 0; loop_x < dimension_x; loop_x++)
		{
			for (int loop_y = 0; loop_y < dimension_y; loop_y++)
			{
				multiplication_number_matrix.set_value(loop_x, loop_y, get_value(loop_x, loop_y) * _number);
			}
		}
		return multiplication_number_matrix;
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::addition_matrix(Matrix &_matrix) const
{
	if (lock_matrix == 0 & dimension_x == _matrix.get_dimension_x() & dimension_y == _matrix.get_dimension_y())
	{
		Matrix addition_matrix(dimension_x, dimension_y);

		for (int loop_x = 0; loop_x < dimension_x; loop_x++)
		{
			for (int loop_y = 0; loop_y < dimension_y; loop_y++)
			{
				addition_matrix.set_value(loop_x, loop_y, get_value(loop_x, loop_y) + _matrix.get_value(loop_x, loop_y));
			}
		}
		return addition_matrix;
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::difference_matrix(Matrix &_matrix) const
{
	if (lock_matrix == 0 & dimension_x == _matrix.get_dimension_x() & dimension_y == _matrix.get_dimension_y())
	{
		Matrix difference_matrix(dimension_x, dimension_y);

		for (int loop_x = 0; loop_x < dimension_x; loop_x++)
		{
			for (int loop_y = 0; loop_y < dimension_y; loop_y++)
			{
				difference_matrix.set_value(loop_x, loop_y, get_value(loop_x, loop_y) - _matrix.get_value(loop_x, loop_y));
			}
		}
		return difference_matrix;
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::operator+(Matrix &_matrix) const
{
	if (lock_matrix == 0 & dimension_x == _matrix.get_dimension_x() & dimension_y == _matrix.get_dimension_y())
	{
		return addition_matrix(_matrix);
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::operator-(Matrix &_matrix) const
{
	if (lock_matrix == 0 & dimension_x == _matrix.get_dimension_x() & dimension_y == _matrix.get_dimension_y())
	{
		return difference_matrix(_matrix);
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::operator*(Matrix &_matrix) const
{	
	if (lock_matrix == 0 & get_dimension_x() == _matrix.get_dimension_y())
	{
		return multiplication_matrix(_matrix);
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::operator*(long double _number) const
{
	if (lock_matrix == 0)
	{
		Matrix multiplication_number_matrix(dimension_x, dimension_y);

		for (int loop_x = 0; loop_x < dimension_x; loop_x++)
		{
			for (int loop_y = 0; loop_y < dimension_y; loop_y++)
			{
				multiplication_number_matrix.set_value(loop_x, loop_y, get_value(loop_x, loop_y) * _number);
			}
		}
		return multiplication_number_matrix;
	}
	else
	{
		return *this;
	}
}

Matrix Matrix::operator=(Matrix &_matrix)
{
	if (_matrix.get_lock_matrix() == 0)
	{   
		lock_matrix = 0;

        dimension_x = _matrix.get_dimension_x();
		dimension_y = _matrix.get_dimension_y();

		if (dimension_x == dimension_y)
		{
			lock_determinant = 0;
		}

		swap_counter = _matrix.get_swap_count();

		delete [] array_matrix;
		array_matrix = new long double[dimension_x * dimension_y];

		reset_matrix();

		for (int loop_x = 0; loop_x < dimension_x; loop_x++)
		{
			for (int loop_y = 0; loop_y < dimension_y; loop_y++)
			{
				set_value(loop_x, loop_y, _matrix.get_value(loop_x, loop_y));
			}
		}
		return *this;
	}
	else
	{
		return *this;
	}
}

Matrix::~Matrix()
{
}
