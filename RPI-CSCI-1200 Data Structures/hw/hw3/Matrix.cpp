#include <cstddef>
#include <iostream>
#include "Matrix.h"

Matrix::Matrix() {
	create(); // Call basic create --> Sets start to NULL pointer and rows + cols to 0
}

Matrix::Matrix(const unsigned int& num_rows, const unsigned int& num_cols, const double& fill) {
	create(num_rows,num_cols,fill); // Call constructor with args
}

void Matrix::create() {
	start = NULL; // Set start to null pointer
	rows = cols = 0;
}

void Matrix::create(const unsigned int& num_rows, const unsigned int& num_cols, const double& fill) {
	// Check for invalid Matrix dimensions -- if rows/cols = 0, then call null constructor
	if ((num_rows==0) || (num_cols==0)) {
		create();
	} else {
		// Set rows and cols to proper value
		rows = num_rows;
		cols = num_cols;
		start = new double*[rows]; // Set start to a pointer of pointers
		for (unsigned int r = 0; r < rows; r++) {
			start[r] = new double[cols]; // each item in start should point to an array of doubles
			for (unsigned int c = 0; c < cols; c++) {
				start[r][c] = fill; // Fill in everything with given value
			}
		}
	}
}

Matrix& Matrix::operator=(const Matrix& m) {
	// Check if using operator on self 	
	if (this != &m) {
		clear(); // Clear old data
    	this -> copy(m); // Copy data from right hand matrix
  	}
  	return *this;
}

void Matrix::copy(const Matrix& m) {
	double ** pointer = m.get_start(); // get pointer to other matrix's data
	// Check if other matrix has data
	if (pointer!=NULL) {
		create(m.num_rows(),m.num_cols(),0); // create with rows and cols equal to other matrix's

		// Copy other matrix's data
		for (unsigned int r=0;r<rows;r++) {
			for (unsigned int c=0;c<cols;c++) {
				start[r][c] = pointer[r][c];
			}
		}
	} else {
		// If other matrix is empty, just initialize an empty matrix
		create();
	}	
}

Matrix::~Matrix() {
	// Delete each array of doubles
	for (unsigned int r=0;r<rows;r++) {
		delete [] start[r];
	}
	// Delete the final array of pointers
	delete [] start;
}
unsigned int Matrix::num_rows() const {
	return rows;
}
unsigned int Matrix::num_cols() const {
	return cols;
}
double** Matrix::get_start() const {
	return start; // Return the pointer to the matrix's data
}
void Matrix::clear() {
	// Delete each array of doubles
	for (unsigned int r=0;r<rows;r++) {
		delete [] start[r];
	}
	// Delete the final array of pointers
	delete [] start;
	create(); // Initialize empty matrix
}
bool Matrix::operator==(const Matrix& m) const {
	// Check if the dimensions of the two matrices are the same
	if ((this->num_rows()==m.num_rows())&&(this->num_cols()==m.num_cols())) {
		// create pointers to other matrix's data
		double** pointer=m.get_start();
		for (unsigned int r=0;r<rows;++r) {
			for (unsigned int c=0;c<cols;++c) {
				// Compare values of each cell in matrix, if different return false
				if (start[r][c]!=pointer[r][c]) {
					return false;
				}
			}
		}
		// Once comparisons are done, all cells must be equal so return true
		return true;
	} else {
		return false;
	}
}
bool Matrix::operator!=(const Matrix& m) const {
	return !(this->operator==(m)); // Return the opposite of the == operator
}

/*Alternative print method that I wrote.
It wasn't required in the HW but I wanted to 
print a matrix with my own formatting for easier debugging*/
void Matrix::print() const {
	std::cout << std::endl << "Start of " << num_rows() << " x " << num_cols() << " Matrix" << std::endl; // demarcate the start of the matrix
	// loop through the 2D array 
	for (unsigned int r=0;r<rows;++r) {
		std::cout << "Row " << r << ":"; // Begin each line with the row number
		for (unsigned int c=0;c<cols;++c) {
			std::cout << " " << start[r][c]; // Print the cell's value
		}
		std::cout << std::endl; // end the line
	}
	std::cout << "End of Matrix" << std::endl; //  demarcate the end of the matrix.
}

bool Matrix::set(const unsigned int& row,const unsigned int& col,const double& val) {
	// Check if specified cell is within matrix bounds
	if ((row<rows)&&(col<cols)) {
		// if yes, set cell to to passed value and return true. 
		start[row][col]=val; 
		return true;
	} else {
		// if not return false
		return false;
	}
}


bool Matrix::get(const unsigned int& row,const unsigned int& col,double& val) const {
	// Check if specified cell is within matrix bounds 
	if ((row<rows)&&(col<cols)) {
		// if yes, set passed value to cell's value and return true
		val = start[row][col];
		return true;
	} else {
		// if not, return false
		return false;
	}
}

void Matrix::multiply_by_coefficient(const double& val) {
	// Loop through start -- the 2D array of all the data
	for (unsigned int r=0;r<rows;r++) {
		for (unsigned int c=0;c<cols;c++) {
			// Multiply each cell by the specified value
			start[r][c]*=val;
		}
	}
}

bool Matrix::swap_row(const unsigned int& row1,const unsigned int&row2) {
	// Check if rows are within the bounds of the matrix
	if ((row1<rows)&&(row2<rows)) {
		// Create a temporary array to hold the first row's data
		double temp[cols];
		for (unsigned int c=0;c<cols;c++) {
			temp[c]=start[row1][c];  // copy row 1's data into temp
			start[row1][c]=start[row2][c]; // replace row 1's data with row 2's
			start[row2][c]=temp[c]; // Replace row 2 with row 1's data from temp
		}
		return true;
	} else {
		return false;
	}
}

void Matrix::transpose() {
	// Create the representation for the new matrix, it's data, # rows, and # cols
	double ** new_data = new double*[cols];
	unsigned int new_rows = cols;
	unsigned int new_cols = rows;
	// The number of rows in the next matrix = # of columns in old matrix
	for (unsigned int r = 0; r < cols; r++) {
		// Number of columns in the new matrix = # of rows in the old matrix
		new_data[r] = new double[rows];
		for (unsigned int c = 0; c < rows; c++) {
			// Each data point is shifted so that row num and col num essentially switch places
			new_data[r][c] = start[c][r];
		}
	}
	// Clear old matrix
	clear(); 

	// Set the old matrix equal to the old matrix
	rows = new_rows;
	cols = new_cols;
	start = new_data;
}

bool Matrix::add(const Matrix& m) {
	// Check if dimensions of two matrices are equal
	if ((rows=m.num_rows())&&(cols==m.num_cols())) {
		// Create pointer to the 2nd matrix's data
		double**pointer = m.get_start();
		// Loop through the 2D arrays
		for (unsigned int r=0;r<rows;r++) {
			for (unsigned int c=0;c<cols;c++) {
				// Each cell in 1st matrix = 1st value + 2nd value
				start[r][c]+=pointer[r][c];
			}
		}
		return true;
	} else {
		return false;
	}
}
bool Matrix::subtract(const Matrix& m) {
	// Check if dimensions of two matrices are equal
	if ((rows=m.num_rows())&&(cols==m.num_cols())) {
		// Create pointer to the 2nd matrix's data
		double**pointer = m.get_start();
		// Loop through the 2D arrays
		for (unsigned int r=0;r<rows;r++) {
			for (unsigned int c=0;c<cols;c++) {
				// Each cell in 1st matrix = 1st value - 2nd value
				start[r][c]-=pointer[r][c];
			}
		}
		return true;
	} else {
		return false;
	}
}

double* Matrix::get_row(const unsigned int& row_num)const {
	// Create the return pointer and initially set it to NULL
	double* return_val = NULL;
	// Check if specified row is within the bounds of the array
	if (row_num<rows) {
		// If so, set return_val equal to point to a new array of doubles
		return_val = new double[cols];
		// copy the values from the specified row (by looping through columns) into the return value
		for (unsigned int c=0;c<cols;c++) {
			return_val[c] = start[row_num][c];
		}
	}
	return return_val;
}
double* Matrix::get_col(const unsigned int& col_num)const {
	// Create the return pointer and initially set it to NULL
	double* return_val = NULL;
	// Check if specified column is within the bounds of the array
	if (col_num<cols) {
		// If so, set return_val to point to a new array of doubles
		return_val = new double[rows];
		// copy the values from the specified column (by looping through the rows) into the return value
		for (unsigned int r=0;r<rows;r++) {
			return_val[r]=start[r][col_num];
		}
	}
	return return_val;
}

Matrix* Matrix::quarter() const {
	// Create a pointer to new array of matrices
	Matrix* return_ms = new Matrix[4];

	// Create 4 matrices with dimensions equal to half the dimensions of the original matrix
	// plus 1 if that dimension is an odd number
	Matrix m1((rows/2)+(rows%2),(cols/2)+(cols%2),0); // m1 = Upper left
	Matrix m2((rows/2)+(rows%2),(cols/2)+(cols%2),0); // m2 = upper right
	Matrix m3((rows/2)+(rows%2),(cols/2)+(cols%2),0); // m3 = lower left
	Matrix m4((rows/2)+(rows%2),(cols/2)+(cols%2),0); // m4 = lower right

	// Loop through the dimensions of one of the smaller quartered matrices
	for (unsigned int r1=0;r1<m1.num_rows();r1++) {
		for (unsigned int c1=0;c1<m1.num_cols();c1++) {
			// copy the values from the upper left quarter of the original matrix
			// rows and columns both start from row 0 and column 0 of original matrix
			m1.set(r1,c1,start[r1][c1]);

			// copy the values from the upper right quarter of the original matrix
			// Rows start from row 0 of the original matrix
			// Columns start from col x where x is half the width minus 1 if the width is odd
			m2.set(r1,c1,start[r1][c1+m2.num_cols()-(cols%2)]);

			// copy the values from the lower left quarter of the original matrix
			// Rows start from row x of the original matrix where x is half the height minus 1 if it's odd
			// Columns start from col 0
			m3.set(r1,c1,start[r1+m3.num_rows()-(rows%2)][c1]);

			// copy the values from the lower right quarter of the original matrix
			// Rows start from row x of the original matrix where x is half the height minus 1 if it's odd
			// Columns start from col x where x is half the width minus 1 if the width is odd
			m4.set(r1,c1,start[r1+m4.num_rows()-(rows%2)][c1+m4.num_cols()-(cols%2)]);
		}
	}
	// Assign each element in the vector to the filled matrices
	return_ms[0]=m1;
	return_ms[1]=m2;
	return_ms[2]=m3;
	return_ms[3]=m4;
	return return_ms;
}

void Matrix::resize(const unsigned int& num_rows,const unsigned int& num_cols,const double& fill) {
	// Create a new matrix 
	Matrix new_matrix(num_rows,new_matrix.num_cols(),fill);
	for (unsigned int r=0;r<new_matrix.num_rows();r++) {
		for (unsigned int c=0;c<num_cols;c++) {
			if ((r<this->num_rows())&&c<this->num_cols())
				new_matrix.set(r,c,start[r][c]);
		}
	}
	this->copy(new_matrix);
}



std::ostream& operator<< (std::ostream& out, const Matrix& m) {
	// Get the start of the matrix's data
	double** pointer=m.get_start();
	// Print the first few lines 
	// R x C matrix
	// [
	out << std::endl << m.num_rows() << " x " << m.num_cols() << " matrix:"<< std::endl << "[ ";

	// loop through the matrix data 
	for (unsigned int r=0;r<m.num_rows();r++) {
		// print the cell value followe by a space
		for (unsigned int c=0;c<m.num_cols();c++) {
			out << pointer[r][c] << " ";
		}
		// if the row isn't the last row, create a new line
		if (r!=m.num_rows()-1) {
			out << std::endl;
		}
	}
	// Finish the last line with a closing bracket
	out << "]" << std::endl;
	return out;
}


