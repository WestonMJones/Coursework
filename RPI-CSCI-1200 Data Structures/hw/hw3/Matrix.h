#ifndef Matrix_h_
#define Matrix_h_
#include <cstddef>
#include <iostream>

class Matrix {
public:
	// Constructors, Assignment Operator, and Destructor
	Matrix(); // Default Constructor
	Matrix(const unsigned int& num_rows, const unsigned int& num_cols, const double& fill); // Constructor with args
	Matrix(const Matrix& m) {copy(m);} // Copy Constructor
	Matrix& operator=(const Matrix& m); // Assignment Operators
	~Matrix(); // Destructor

	// Clear Function
	void clear();

	// Comparison Operators
	bool operator==(const Matrix& m)const;
	bool operator!=(const Matrix& m)const;

	// Accessor Functions
	unsigned int num_rows() const;
	unsigned int num_cols() const;
	double** get_start() const;
	bool get(const unsigned int& row,const unsigned int& col,double& val) const;
	double* get_row(const unsigned int& row_num)const;
	double* get_col(const unsigned int& col_num)const;

	// Setter Function
	bool set(const unsigned int& row,const unsigned int& col,const double& val);

	// Binary Matrix Operations
	bool add(const Matrix& m);
	bool subtract(const Matrix& m);

	// Other Functions
	void multiply_by_coefficient(const double& val);
	bool swap_row(const unsigned int& row1,const unsigned int&row2);
	void transpose();
	Matrix* quarter() const;
	void print() const;
	void resize(const unsigned int& num_rows,const unsigned int& num_cols,const double& fill);

	
private:
	// Representation
	double** start; // Pointer to the pointer of pointers that accesses the Matrix data
	unsigned int rows; // Number of rows
	unsigned int cols; // Number of columns

	// Private initialization methods
	void create();
	void create(const unsigned int& num_rows, const unsigned int& num_cols, const double& fill);
	void copy(const Matrix& m);
};
std::ostream& operator<< (std::ostream& out, const Matrix& m); // Overloaded << Operator
#endif