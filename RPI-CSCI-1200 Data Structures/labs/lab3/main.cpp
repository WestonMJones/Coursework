#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>


void compute_squares(unsigned int a[], unsigned int b[], unsigned int n) {
	int counter = 1;
	unsigned int *p2a;
	unsigned int *p2b;
	for (p2a=a; p2a<a+n;p2a++) {
		
		p2b = p2a;
		std::cout <<counter << ". The original value of a was: " << *p2a;
		*p2a = (*p2a)*(*p2a);
		*p2b = *p2a;
		std::cout << " and the new values of a and b are: " << *p2a << " and " << *p2b << " respectively." << std::endl;
		counter = counter + 1;
	}
}


int main(int argc, char* argv[]) {
	// Normal Functioning
	unsigned int a1[] = {1,2,3,4,5};
	unsigned int b1[] = {0,0,0,0,0};
	compute_squares(a1,b1,5);

	std::cout << "End of a Test" << std::endl << std::endl;

	// N is smaller than array length
	unsigned int a2[] = {1,2,3,4,5,6,7,8};
	unsigned int b2[] = {0,0,0,0,0,0,0,0};
	compute_squares(a2,b2,5);

	std::cout << "End of a Test" << std::endl << std::endl;

	// B array is bigger -- leads to unused memory
	unsigned int a3[] = {2,4,6,8};
	unsigned int b3[] = {0,0,0,0,0,0};
	compute_squares(a3,b3,4);

	std::cout << "End of a Test" << std::endl << std::endl;

	// N is bigger than array length --  Seg fault
	unsigned int a4[] = {45,76,34};
	unsigned int b4[] = {0,0,0};
	compute_squares(a4,b4,5);

	std::cout << "End of a Test" << std::endl << std::endl;

	// B array is smaller -- leads to seg fault
	unsigned int a5[] = {10,20,30,40,50,60};
	unsigned int b5[] = {0,0,0,0};
	compute_squares(a5,b5,6);

	std::cout << "End of a Test" << std::endl << std::endl;





	return 0;
}