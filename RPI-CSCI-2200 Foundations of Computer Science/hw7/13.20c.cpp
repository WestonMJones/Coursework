#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>

int main(int argc, char* argv[]) {

	for (int sum=0;sum<30;sum++) {
		int count = 0;
		for (int a=0;a<9;a++) {
			for (int b=0;b<9;b++) {
				for (int c=0;c<9;c++) {
					for (int d=0;d<9;d++) {
						for (int e=0;e<9;e++) {
							for (int f=0;f<9;f++) {

								int number = (a*100000) + (b*10000) + (c*1000) + (d*100) + (e*10) + f;
								int digits = a+b+c+d+e+f;
								if (digits==sum) {
									count++;
									//std::cout << std::setw(6) << std::setfill('0') << number << std::endl;
								}
								

							}
						}
					}
				}
			}
		}
		std::cout << "When S="<<sum<< " then n="<<count<<std::endl;
	}


	

  
	return 0;
}