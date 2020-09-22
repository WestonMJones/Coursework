#include <fstream>
#include <iostream>
#include <list>
#include <vector>


int UghRecursion(int x, int y) {

	if ((x==0)||(y==0)) {
		return 1;
	} else {
		return UghRecursion(x-1,y) +UghRecursion(x,y-1);
	}
}


int main() {

	std::cout << "Enter in the x and y coordinates respectively" << std::endl;
	unsigned int start_x, start_y;
	std::cin >> start_x >> start_y;
	std::cout << "Starting cooridinates are x="<<start_x<<" and y="<<start_y<<std::endl;
	std::cout << std::endl << "The number of paths to return to the origin is: " << UghRecursion(start_x,start_y);



	return 0; 
}