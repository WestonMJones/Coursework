// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =======================================================


#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

#define __EPSILON 0.0000000001 //Need this to compare doubles because representation.

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here
void ExtraCreditTest(); //Write this if you write resize()


//Function to test a ton of matrices at once.
void BatchTest(double start, double step, unsigned int rows, unsigned int cols,
               unsigned int num);

//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b);

//Uses Gauss-Jordan elimination to create a Reduced Row Echelon Form matrix.
Matrix rref(const Matrix& m);

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	//Uncomment this to allocate a lot of 100x100 matrices so leaks will be bigger.
	
	BatchTest(100,0.1,100,100,50);
	std::cout << "Completed all batch tests." << std::endl;
	

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	//Uncomment this if you write the resize() function.
	
	ExtraCreditTest();
	std::cout << "Completed all student extra credit tests." << std::endl;
	
	return 0;
}

////////////////Test functions//////////////////////
//Some basic tests
void SimpleTest(){  //well behaved getrow/read after
	//Default constructor
	Matrix m1;
	assert(m1.num_rows() == 0 && m1.num_cols() == 0);

	//Copy constructor
	Matrix m2(3,4,0);
	assert(m2.num_rows() == 3 && m2.num_cols() == 4);

	Matrix m2_copy(m2);
	assert(m2_copy.num_rows() == 3 && m2_copy.num_cols() == 4);
	m2_copy.set(1,1,27);
	double d0;
	assert(m2.get(1,1,d0));
	assert(double_compare(d0,0.0));
	assert(m2_copy.get(1,1,d0));
	assert(double_compare(d0,27));

	//Equality and Inequality
	Matrix m3;
	assert(m1 == m3);
	assert(m1 != m2);

	//Printing
	std::cout << "Empty matrix:";
	std::cout << m1 << std::endl;

	std::cout << "Zeroed 3x4 matrix:";
	std::cout << m2 << std::endl;

	std::cout << "One after the other:";
	std::cout << m1 << m2 << std::endl;

	//Set & get
	Matrix m5(4,4,2);
	Matrix m6(4,4,12);
	assert(m6.set(2,1,7));
	assert(m6.set(3,3,11));
	double d1;
	assert(m6.get(2,1,d1));
	assert(d1==7);

	//Addition
	std::cout << "Adding m5 and m6" << std::endl;
	std::cout << m5 << m6 << std::endl;

	Matrix m7;
	m7 = m5;
	Matrix m8(m5);
	assert(m7 == m8);

	assert(m7.add(m6));
	std::cout << "The result" << std::endl;
	std::cout << m7 << std::endl;

	double* r1 = NULL;
	r1 = m7.get_row(2);
	assert(r1[0] == 14 && r1[1] == 9);

	delete [] r1; //Remember we need to clean up dynamic allocations.

	Matrix m9(3,6,0);
	m9.set(0,0,1);
	m9.set(0,1,2);
	m9.set(0,2,1);
	m9.set(0,3,1);
	m9.set(1,0,2);
	m9.set(1,1,3);
	m9.set(1,2,-1);
	m9.set(1,4,1);
	m9.set(2,0,3);
	m9.set(2,1,-2);
	m9.set(2,2,-1);
	m9.set(2,5,1);

	std::cout << "Attempting Gauss-Jordan reduced row echelon form." 
		  << m9 << std::endl;
	Matrix m12 = rref(m9);
	std::cout << m12 << std::endl;
	double comparison_value;
	assert(m12.get(0,3,comparison_value));
	assert(double_compare(comparison_value,0.25));
	assert(m12.get(0,1,comparison_value));
	assert(double_compare(comparison_value,0.0));
	assert(m12.get(1,5,comparison_value));
	assert(double_compare(comparison_value,-3.00/20));
	assert(m9.get(0,3,comparison_value));
	assert(double_compare(comparison_value,1.0));
	assert(m9.get(0,1,comparison_value));
	assert(double_compare(comparison_value,2.0));
	assert(m9.get(1,5,comparison_value));
	assert(double_compare(comparison_value,0.0));

	Matrix m11(3,4,0);
	m11.set(0,0,1);
	m11.set(0,1,2);
	m11.set(0,2,3);
	m11.set(0,3,4);

	m11.set(1,0,5);
	m11.set(1,1,6);
	m11.set(1,2,7);
	m11.set(1,3,8);

	m11.set(2,0,9);
	m11.set(2,1,10);
	m11.set(2,2,11);
	m11.set(2,3,12);

	std::cout << "M11 to be quartered: " << std::endl;
	std::cout << m11 << std::endl;
	Matrix* ma1 = NULL;
	ma1 = m11.quarter();
	assert(ma1 != NULL);

	std::cout << "UL: " << std::endl << ma1[0] << std::endl;
	std::cout << "UR: " << std::endl << ma1[1] << std::endl;
	std::cout << "LL: " << std::endl << ma1[2] << std::endl;
	std::cout << "LR: " << std::endl << ma1[3] << std::endl;

	for(unsigned int i=0; i<4; i++){
		assert((ma1[i].num_rows() == 2) && (ma1[i].num_cols() == 2));
	}

	//Upper Left
	assert(ma1[0].get(0,0,comparison_value));
	assert(double_compare(comparison_value,1));
	assert(ma1[0].get(1,1,comparison_value));
	assert(double_compare(comparison_value,6));

	//Upper Right
	assert(ma1[1].get(0,0,comparison_value));
	assert(double_compare(comparison_value,3));
	assert(ma1[1].get(1,1,comparison_value));
	assert(double_compare(comparison_value,8));

	//Lower Left
	assert(ma1[2].get(0,0,comparison_value));
	assert(double_compare(comparison_value,5));
	assert(ma1[2].get(1,1,comparison_value));
	assert(double_compare(comparison_value,10));

	//Lower Right
	assert(ma1[3].get(0,0,comparison_value));
	assert(double_compare(comparison_value,7));
	assert(ma1[3].get(1,1,comparison_value));
	assert(double_compare(comparison_value,12));

	delete [] ma1;
}

//Write your own test cases here
void StudentTest(){

	// Test Constructors
	Matrix m1(3,3,0);
	Matrix m2(0,5,3);
	Matrix m3(5,0,4);
	Matrix m4;
	Matrix m5(m1);
	Matrix m6(4,5,73);

	std::cout << std::endl << "Testing Constructors" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;
	std::cout << m3 << std::endl;
	std::cout << m4 << std::endl;
	std::cout << m5 << std::endl;
	std::cout << m6 << std::endl;

	// Test Equality operators
	std::cout << std::endl << "Testing Equality Operators" << std::endl;
	assert(m1==m5);
	assert(m2==m3);
	assert(m3==m4);
	assert(m1!=m6);
	assert(m6!=m3);

	// Test clear method
	std::cout << std::endl << "Testing Clear Method" << std::endl;
	m1.clear();
	m1.clear();
	m1.clear();
	m2.clear();
	m2.clear();
	m2.clear();
	m3.clear();
	m3.clear();
	m3.clear();
	m4.clear();
	m4.clear();
	m4.clear();
	m5.clear();
	m5.clear();
	m5.clear();
	m6.clear();
	m6.clear();
	m6.clear();

	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;
	std::cout << m3 << std::endl;
	std::cout << m4 << std::endl;
	std::cout << m5 << std::endl;
	std::cout << m6 << std::endl;

	// Testing Getter and Setter Methods
	std::cout << std::endl << "Testing Getter and Setter Methods" << std::endl;

	Matrix m8(4,2,0);
	double test_val = 0;

	// These should all work
	m8.set(0,0,1);
	m8.set(0,1,2);
	m8.set(1,0,3);
	m8.set(1,1,4);
	m8.set(2,0,5);
	m8.set(2,1,6);
	m8.set(3,0,7);
	m8.set(3,1,8);

	m8.print();

	// These shouldn't work but shouldn't throw errors either
	m8.set(4,2,73);
	m8.set(55,61,99);
	m8.set(56,1,42);
	m8.set(3,20,69);

	m8.print();

	// Test getter -- these should all work
	m8.get(2,0,test_val);
	assert(test_val==5);
	m8.get(3,1,test_val);
	assert(test_val==8);
	m8.get(0,0,test_val);
	assert(test_val==1);

	// Test getter -- these shouldn't work but should return errors either
	m8.get(73,42,test_val);
	m8.get(-1,-5,test_val);
	m8.get(0,67,test_val);
	m8.get(67,0,test_val);
	m8.get(-1,3,test_val);
	assert(test_val==1);
	
	// Test multiply by coefficient
	std::cout << std::endl << "Testing Multiply by coefficient" << std::endl;
	m8.print();
	m8.multiply_by_coefficient(2);
	m8.print();
	m8.multiply_by_coefficient(2);
	m8.print();
	m8.multiply_by_coefficient(1000);
	m8.print();

	// Test Swap Row
	std::cout << std::endl << "Testing Swap Row" << std::endl;
	m8.print();
	m8.swap_row(3,4); // shouldn't do anything
	m8.print();
	m8.swap_row(2,3);
	m8.print();
	m8.swap_row(1,2);
	m8.print();
	m8.swap_row(0,1);
	m8.print();

	Matrix m9;
	m9.swap_row(0,0);
	m9.print();

	// Test transpose matrix
	std::cout << std::endl << "Testing transpose" << std::endl;
	m8.print();
	m8.transpose();
	m8.print();
	m8.transpose();
	m8.print();
	std::cout << std::endl << "Other Matrix" << std::endl;
	m9.print();
	m9.transpose();
	m9.print();
	m9.transpose();
	m9.print();


	m8.clear();
	m9.clear();

	// Test Add and Subtract Matrices
	std::cout << std::endl << "Testing Matrix addition" << std::endl;

	Matrix m10(5,5,5);
	Matrix m11(5,5,7);
	Matrix m12(5,6,3);

	m10.print();
	m10.add(m11);
	m10.add(m12); // Shouldn't work
	m10.print();

	std::cout << std::endl << "Testing Matrix subtraction" << std::endl;
	m10.print();
	m10.subtract(m11);
	m10.subtract(m12); // Shouldn't work
	m10.print();

	// Test get_row
	std::cout << std::endl << "Testing Get Row" << std::endl;
	Matrix m13(7,2,0);
	m13.set(6,0,42);
	m13.set(6,1,73);
	m13.print();

	double* row = NULL;
	row = m13.get_row(6);
	assert(row[0] == 42 && row[1] == 73);

	delete [] row; 


	// Test get column
	std::cout << std::endl << "Testing Get Column" << std::endl;
	Matrix m14(2,7,0);
	m14.set(0,6,42);
	m14.set(1,6,73);
	m14.print();
	double* col = NULL;
	col = m14.get_col(6);
	assert(col[0] == 42 && col[1] == 73);

	delete [] col;

	// Test Quarter
	std::cout << std::endl << "Testing Quarter -- Test Case 1" << std::endl;

	Matrix m15(5,5,0);
	for (unsigned int r=0;r<m15.num_rows();r++) {
		for (unsigned int c=0;c<m15.num_cols();c++) {
			m15.set(r,c,r*c);
		}
	}
	m15.print();

	Matrix* a = m15.quarter();
	for (Matrix * pointer=a;pointer<a+4;pointer++) {
		pointer->print();
	}

	delete [] a;

	std::cout << std::endl << "Testing Quarter -- Test Case 2" << std::endl;

	Matrix m16(4,4,0);
	for (unsigned int r=0;r<m16.num_rows();r++) {
		for (unsigned int c=0;c<m16.num_cols();c++) {
			m16.set(r,c,r+c+1);
		}
	}
	m16.print();

	Matrix* b = m16.quarter();
	for (Matrix * pointer=b;pointer<b+4;pointer++) {
		pointer->print();
	}

	delete [] b;

	std::cout << std::endl << "Testing Quarter -- Test Case 3" << std::endl;

	Matrix m17(5,0,0);
	m17.print();

	Matrix* c = m17.quarter();
	for (Matrix * pointer=c;pointer<c+4;pointer++) {
		pointer->print();
	}

	delete [] c;
}

//Write this if you write resize()
void ExtraCreditTest(){
	/*Matrix m1(10,10,73);
	m1.resize(20,20,42);
	m1.print();*/
}


////////////////Utility functions//////////////////////

/*  Function that quickly populates a rows x cols matrix with values from     
 *  start in increments of step. Does this num_times times.
 */
void BatchTest(double start, double step, unsigned int rows, unsigned int cols,
               unsigned int num){
	Matrix* m_arr = new Matrix[num];
	for(unsigned int i=0; i<num; i++){
		m_arr[i] = Matrix(rows,cols,0.0);
		unsigned int curr_elem = 0;
		for(unsigned int j=0; j<rows; j++){
			for(unsigned int k=0; k<rows; k++){
				m_arr[i].set(j,k,start+(step*curr_elem));
				curr_elem++;
			}
		}
	}
	delete [] m_arr;
}

//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b){
	return (fabs(a-b) < __EPSILON);
}

/*  Uses Gauss-Jordan elimination to create a Reduced Row Echelon Form matrix.
 *  These are some good and some bad variable names.
 *  See how much harder it makes it to follow the code?
 *  The lack of comments doesn't help either.
 */

Matrix rref(const Matrix& m){
	Matrix ret(m);
	unsigned int curr_col = 0;
	double dummy;
	for(unsigned int i=0; i<ret.num_rows(); i++){
		bool col_all_zeros = true;
		while(col_all_zeros && col_all_zeros < ret.num_cols()){
			for(unsigned int scan_i = 0; scan_i < ret.num_rows(); scan_i++){
				ret.get(scan_i,curr_col,dummy);
				if (!double_compare(dummy,0.0)){
					col_all_zeros = false;
					break;
				}
			}
			if(col_all_zeros){
				curr_col += 1;
			}
		}
		if(curr_col>=ret.num_cols()){
			return ret;
		}

		ret.get(i,curr_col,dummy);
		if(double_compare(dummy,0.0)){
			//Swap with a nonzero row
			for(unsigned int scan_i = i+1; scan_i < ret.num_rows(); scan_i++){
				ret.get(scan_i,curr_col,dummy);
				if(!double_compare(dummy,0.0)){
					ret.swap_row(scan_i,i);
					break;
				}
			}
		}

		//Now we know ret i,curr_col is non-zero so we can use it as a pivot.
		double pivot;
		ret.get(i,curr_col,pivot);
		for(unsigned int j=0; j<ret.num_cols(); j++){
			ret.get(i,j,dummy);
			ret.set(i,j,dummy/pivot);
		}

		for(unsigned int row_i = 0; row_i < ret.num_rows(); row_i++){
			if (row_i == i){
				continue;
			}
			double row_leading_coeff;
			ret.get(row_i,curr_col,row_leading_coeff);
			for(unsigned int col_j = 0; col_j < ret.num_cols(); col_j++){
				double lhs_dummy,rhs_dummy;
				ret.get(row_i,col_j,lhs_dummy);
				ret.get(i,col_j,rhs_dummy);
				ret.set(row_i,col_j,lhs_dummy - (row_leading_coeff*rhs_dummy));
			}
		}
		curr_col +=1 ;
	}
	return ret;
}
