#include <fstream>
#include <iostream>
#include <list>
#include <vector>


int UghRecursion(int x, int y, int end_x, int end_y) {

	if (x>end_x) {
		return 0;
	}

	if (y>end_y) {
		return 0;
	}

	if ((x==end_x)||(y==end_y)) {
		return 1;
	} else {
		return UghRecursion(x+1,y,end_x,end_y) + UghRecursion(x,y+1,end_x,end_y);
	}
	
}


int main() {

	for (int i=0;i<5;i++) {
		for (int j=0;j<5;j++) {
			std::cout << "If we go to point (" << i <<", "<<j<<") then there are " << UghRecursion(0,0,i,j) << " paths." << std::endl;
		}
	}

	
	


	return 0; 
}