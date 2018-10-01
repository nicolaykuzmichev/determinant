class Matrix // class Matrix
{
private: // private fields and methods
	
	long double *array_matrix; // dynamic array of data matrix

	int dimension_x; // number of columns
	int dimension_y; // number of rows
	int swap_counter; // number of swaps of rows and columns
	int lock_determinant; // lock flag for calculation determinant
	int lock_matrix; // lock flag for operations with matrix

	long double method_algebraic_additions_counter(long double **_array_of_minors, int _dimension); // calculation determinant with algebraic additions
	Matrix method_Gauss_counter(); // calculation determinant with method Gauss

public: // public fields and methods

	Matrix(int _dimension_x, int _dimension_y); // costructor class
	Matrix(const Matrix &_matrix); // constructor class (copying)

	long double set_value(int _row, int _column, long double _value); // change value element
	long double get_value(int _row, int _column) const; // output value element

	int swap_rows(int _first_row_index, int _second_row_index); // swap rows
	int swap_columns(int _first_column_index, int _second_column_index); // swap columns

	long double count_determinant_matrix(int _method = 0); //calculation determinant

	int get_swap_count() const; // output number swaps rows and columns
	int get_dimension_x() const; // output number columns
	int get_dimension_y() const; // output number rows
	int get_lock_matrix() const; // output value lock matrix flag
	int get_lock_determinant() const; // output value lock determinant flag
	int rank_matrix(); // calculation value rank matrix
	long double trace_matrix() const; // calculation value trace matrix

	int reset_matrix(); // reset matrix

	Matrix inverse_matrix(); // calculation inverse matrix

	Matrix transpose_matrix() const; // calculation transpose matrix

	Matrix multiplication_matrix(Matrix &_matrix) const; // multiplication two matrix

	Matrix multiplication_matrix_on_number(long double _number) const; // multiplication matrix on number

	Matrix addition_matrix(Matrix &_matrix) const; // addition two matrix

	Matrix difference_matrix(Matrix &_matrix) const; // difference two matrix

	Matrix operator+(Matrix &_matrix) const; // overload operator + for class Matrix
	Matrix operator-(Matrix &_matrix) const; // overload operator - for class Matrix
	Matrix operator*(Matrix &_matrix) const; // first overload operator * for class Matrix
	Matrix operator*(long double _number) const; // second overload operator * for class Matrix
	Matrix operator=(Matrix &_matrix); // overload operator = for class Matrix

	~Matrix(); // destructor class
};

