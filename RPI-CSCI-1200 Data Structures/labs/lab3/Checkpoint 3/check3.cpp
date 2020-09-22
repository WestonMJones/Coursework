
#include <cstdlib>    // library with the exit function
#include <iostream>
#include <string> 
#include "time.h"
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <iomanip>
#include <string>

// GLOBAL VARIABLES used by print_stack, label_stack, and clear_stack
std::vector<uintptr_t*> GLOBAL_addresses;
std::vector<std::string> GLOBAL_labels;


// ==============================================================================
//
// This function does a limited print of the data stored on the stack
// in the range of the addresses currently "labeled" and stored in the
// global variables above.
//
// To make the output more readable, the function assumes that integer
// "values" will be between -1000 & 1000 and addresses will be within
// +/- 1000*4 (or *8) bytes from any of the labeled addresses.
// Anything else is assumed to be "garbage"
//
void print_stack() { 

  assert (GLOBAL_addresses.size() == GLOBAL_labels.size());
  if (GLOBAL_addresses.size() == 0) {
    std::cerr <<  "No labeled addresses to print" << std::endl;
    return;
  }

  // Identify the range of stack data to print
  uintptr_t* min_address = GLOBAL_addresses[0];
  uintptr_t* max_address = GLOBAL_addresses[0];
  int max_label_width = GLOBAL_labels[0].size();
  for (int i = 1; i < GLOBAL_addresses.size(); i++) {
    if (GLOBAL_addresses[i] > max_address) { max_address = GLOBAL_addresses[i]; }
    if (GLOBAL_addresses[i] < min_address) { min_address = GLOBAL_addresses[i]; }
    if (GLOBAL_labels[i].size() > max_label_width) { max_label_width = GLOBAL_labels[i].size(); }
  }

  // double check that my uintptr_t is actually the size of a pointer
  assert (sizeof(uintptr_t) == sizeof(void*));
  // double check that the start and end address are aligned 
  assert ((((uintptr_t)min_address) & (sizeof(uintptr_t)-1)) == 0);
  assert ((((uintptr_t)max_address) & (sizeof(uintptr_t)-1)) == 0);

  // double check that the range of address is reasonable 
  if (max_address-min_address > 1000) {
    std::cerr << "WARNING: trying to print too much" << std::endl;
    return;
  }

  // loop over all addresses in the range (plus some above & below)
  std::cout << "-----------------------------------------" << std::endl;
  for (uintptr_t* address = max_address+5; address >= min_address-5; address--) {
    std::string label = "";
    for (int i = 0; i < GLOBAL_addresses.size(); i++) {
      if (address == GLOBAL_addresses[i]) { label = GLOBAL_labels[i]; }
    }
    std::cout << std::setw(max_label_width) << label << " location: " << address;

    // this location might store a value (we assume all values are integers)
    int an_int = (int)(*address);
    // or it might store an address (so we cast it to a pointer)
    uintptr_t* an_address = (uintptr_t*)(*address);

    // if it's a value
    if (an_int > -1000 && an_int < 1000) {
      std::cout << "  VALUE:   " << an_int << std::endl;
    } 
    // if it's an address
    else if (an_address >= min_address-1000 && an_address <= max_address+1000) {
      std::cout << "  POINTER: " << an_address << std::endl;
    }
    // otherwise it's probably garbage
    else { 
      std::cout << "  garbage? " << std::endl;
    }
  }
  std::cout << "-----------------------------------------" << std::endl;
}


// add a label to a particular address in the stack
// NOTE: We use global variables for simplicity for this exercise
void label_stack(uintptr_t* address, const std::string& tag) {
  for (int i = 0; i < GLOBAL_addresses.size(); i++) {
    // check to see if that address is already labeled
    if (address == GLOBAL_addresses[i]) {
      // add additional labels
      GLOBAL_labels[i] += ", " + tag;      
      return;
    }
  }
  GLOBAL_addresses.push_back(address);
  GLOBAL_labels.push_back(tag);
}


// clear all previous labels
// NOTE: We use global variables for simplicity for this exercise
void clear_stack_labels() {
  GLOBAL_addresses.clear();
  GLOBAL_labels.clear();
}

void change_times(Time& t1, Time t2) {

	label_stack((uintptr_t*)&t1,"t1");
	label_stack((uintptr_t*)&t2,"t2");
	
	print_stack();
	std::cout << "After Edits"<<std::endl;
	std::cout << "t1 address: " << &t1 << std::endl;
 	std::cout << "t2 address: " << &t2 << std::endl;

	t1.setHour(t1.getHour()*3);
	t1.setMinute(t1.getMinute()*3);
	t1.setSecond(t1.getSecond()*3);

	t2.setHour(t2.getHour()*3);
	t2.setMinute(t2.getMinute()*3);
	t2.setSecond(t2.getSecond()*3);\

	print_stack();





}

int main() {
	
	std::cout << "The size of time is: "<< sizeof(Time) << std::endl;
	/* std::cout << "size of uintptr_t: " << sizeof(uintptr_t) << std::endl;
  uintptr_t x = 72;
  uintptr_t a[5] = {10, 11, 12, 13, 14};
  uintptr_t *y = &x;
  uintptr_t z = 98;
  std::cout << "x address: " << &x << std::endl;
  std::cout << "a address: " << &a << std::endl;
  std::cout << "y address: " << &y << std::endl;
  std::cout << "z address: " << &z << std::endl;

  // label the addresses you want to examine on the stack
  label_stack(&x,"x");
  label_stack(&a[0],"a[0]");
  label_stack(&a[4],"a[4]");
  label_stack((uintptr_t*)&y,"y");
  label_stack(&z,"z");

  // print the range of the stack containing these addresses
  print_stack();

  // clear the previous labels
  clear_stack_labels();
*/

	Time t1(5,5,5);
	Time t2(73,73,73);

	label_stack((uintptr_t*)&t1,"time1");
	label_stack((uintptr_t*)&t2,"time2");
	print_stack();


	change_times(t1,t2);


	


	/*Time t1(3,54,33);
	Time t2;
	Time t3(3,54,9);


	std::cout << "Testing getter methods" << std::endl;
	std::cout << "Time 1 is " << t1.getHour() << " hours " << t1.getMinute() << " minutes and " << t1.getSecond() << " seconds." << std::endl;
	std::cout << "Time 2 is " << t2.getHour() << " hours " << t2.getMinute() << " minutes and " << t2.getSecond() << " seconds." << std::endl;
	std::cout << "Time 3 is " << t3.getHour() << " hours " << t3.getMinute() << " minutes and " << t3.getSecond() << " seconds." << std::endl;


	std::cout << std::endl << "Testing setter methods." << std::endl;
	t1.setHour(0);
	t1.setMinute(0);
	t1.setSecond(0);
	t2.setHour(12);
	t2.setMinute(0);
	t2.setSecond(1);
	t3.setHour(14);
	t3.setMinute(4);
	t3.setSecond(5);

	std::cout << "Time 1 is " << t1.getHour() << " hours " << t1.getMinute() << " minutes and " << t1.getSecond() << " seconds." << std::endl;
	std::cout << "Time 2 is " << t2.getHour() << " hours " << t2.getMinute() << " minutes and " << t2.getSecond() << " seconds." << std::endl;
	std::cout << "Time 3 is " << t3.getHour() << " hours " << t3.getMinute() << " minutes and " << t3.getSecond() << " seconds." << std::endl;


	std::cout << std::endl;

	std::cout << "Standard Version of t1 is: ";
	t1.PrintAmPm();
	std::cout << std::endl;

	std::cout << "Standard Version of t2 is: ";
	t2.PrintAmPm();
	std::cout << std::endl;

	std::cout << "Standard Version of t3 is: ";
	t3.PrintAmPm();
	std::cout << std::endl;

	std::cout << std::endl << "Testing Checkpoint 3 Stuff" << std::endl;
	Time t10(0,0,0);
	Time t11(5,5,5);
	Time t12(5,5,5);
	Time t13(12,0,1);
	Time t14(12,0,2);
	Time t15(16,8,3);
	Time t16(5,9,3);
	Time t17(5,9,3);
	Time t18(5,9,3);
	Time t19(2,7,35);
	Time t20(2,7,36);

	std::vector<Time> times;
	times.push_back(t10);
	times.push_back(t11);
	times.push_back(t12);
	times.push_back(t13);
	times.push_back(t14);
	times.push_back(t15);
	times.push_back(t16);
	times.push_back(t17);
	times.push_back(t18);
	times.push_back(t19);
	times.push_back(t20);

	sort(times.begin(), times.end(), IsEarlierThan);

	for (unsigned int x = 0; x<times.size();++x) {
		times[x].PrintAmPm();
		std::cout << std::endl;
	}
	return 0;

	// g++ *.cpp -o Time_test.exe -Wall  --TO COMPILE
	// ./Time_test.exe 					 --TO RUN*/
	return 0;
}