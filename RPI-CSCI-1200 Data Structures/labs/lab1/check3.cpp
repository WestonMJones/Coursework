#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function

int main() {
  //Get first
  std::cout << "Enter first digit" << std::endl;
  int len;
  std::cin >> len;

  //Get rest of sequence
  std::cout << "Enter other digits" << std::endl;
  float nums[len];
  float sum = 0;
  for (int i=0;i<(len);i=i+1) {
  	std::cin >> nums[i];
  	sum = sum + nums[i];
  }

  //Calculate average
  std::cout << "Output average" << std::endl;
  float average = sum / len;
  std::cout<<average << std::endl;

  std::cout << "Stuff less than average" << std::endl;
  for (int i=0;i<(len);i=i+1) {
  	if (nums[i]<average) {
  		  std::cout << nums[i] << std::endl;
  	}
  }



  // by convention, main should return zero when the program finishes normally
  return 0; 
}