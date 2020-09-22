#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>


// NOTE: For this lab we'll use "uintptr_t", a specially defined
// integer type that is the same size in memory as a pointer.  We'll
// use this type everywhere, instead of "int".  On 32 bit
// machines/compilers, this type is probably 4 bytes, and on 64 bit
// machines/compilers, this is probably 8 bytes.


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


// ==============================================================================

void compute_squares(uintptr_t a[], uintptr_t b[], uintptr_t n) {
  uintptr_t counter = 1;
  uintptr_t *p2a;
  uintptr_t *p2b = b;
  for (p2a=a; p2a<a+n;p2a++) {
    std::cout <<counter << ". The original value of a was: " << *p2a;
    *p2a = (*p2a)*(*p2a);
    *p2b = *p2a;
    std::cout << " and the new values of a and b are: " << *p2a << " and " << *p2b << " respectively." << std::endl;
    counter = counter + 1;
    p2b++;
  }
}
int main() {

  // ------------------------------
  // Example code using print_stack
  // ------------------------------
  std::cout << "size of uintptr_t: " << sizeof(uintptr_t) << std::endl;
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


  // continue with lab exercises
  


  /*// Normal Functioning -- Test 1
  uintptr_t a1[] = {1,2,3,4,5};
  uintptr_t b1[] = {0,0,0,0,0};

  std::cout << "Test Case 1 -- Normal Functioning";
  label_stack(&a1[0],"a1[0]");
  label_stack(&b1[0],"b1[0]");
  label_stack(&a1[4],"a1[4]");
  label_stack(&b1[4],"b1[4]");

  std::cout <<std::endl << "Before Running" << std::endl;

  print_stack();

  std::cout <<std::endl << "After Running" << std::endl;
  
  compute_squares(a1,b1,5);

  print_stack();

  std::cout << "End of a Test" << std::endl << std::endl;
  
  clear_stack_labels();
  // End of a test case


  // N is smaller than array length -- Test 2
  uintptr_t a2[] = {1,2,3,4,5,6,7,8};
  uintptr_t b2[] = {0,0,0,0,0,0,0,0};
  std::cout << "Test Case 2 -- N is smaller than array length";
  label_stack(&a2[0],"a2[0]");
  label_stack(&b2[0],"b2[0]");
  label_stack(&a2[4],"a2[4]");
  label_stack(&b2[4],"b2[4]");
  std::cout <<std::endl << "Before Running" << std::endl;

  print_stack();

  std::cout <<std::endl << "After Running" << std::endl;
  compute_squares(a2,b2,5);
  print_stack();

  std::cout << "End of a Test" << std::endl << std::endl;
  
  clear_stack_labels();
  // End of a test case

  // B Arrray is bigger -- Test 3
  uintptr_t a3[] = {1,2,3,4};
  uintptr_t b3[] = {0,0,0,0,0,0};
  std::cout << "Test Case 3 -- B array is bigger";
  label_stack(&a3[0],"a3[0]");
  label_stack(&b3[0],"b3[0]");
  label_stack(&a3[4],"a3[4]");
  label_stack(&b3[4],"b3[4]");
  std::cout <<std::endl << "Before Running" << std::endl;

  print_stack();

  std::cout <<std::endl << "After Running" << std::endl;
  compute_squares(a3,b3,4);
  print_stack();

  std::cout << "End of a Test" << std::endl << std::endl;
  
  clear_stack_labels();
  // End of a test case

  // Test 4 -- N is bigger than array length
  uintptr_t a4[] = {1,2,3,4,5};
  uintptr_t b4[] = {0,0,0,0,0};
  std::cout << "Test Case 4 -- N is bigger than array length";
  label_stack(&a4[0],"a4[0]");
  label_stack(&b4[0],"b4[0]");
  label_stack(&a4[4],"a4[4]");
  label_stack(&b4[4],"b4[4]");
  std::cout <<std::endl << "Before Running" << std::endl;

  print_stack();

  std::cout <<std::endl << "After Running" << std::endl;
  compute_squares(a4,b4,10);
  print_stack();

  std::cout << "End of a Test" << std::endl << std::endl;
  
  clear_stack_labels();
  // End of a test case

  // Test 5 -- B array is smaller
  uintptr_t a5[] = {1,2,3,4,5,6,7,8};
  uintptr_t b5[] = {0,0,0,0};
  std::cout << "Test Case 5 -- B Array is smaller";
  label_stack(&a5[0],"a5[0]");
  label_stack(&b5[0],"b5[0]");
  label_stack(&a5[4],"a5[4]");
  label_stack(&b5[4],"b5[4]");
  std::cout <<std::endl << "Before Running" << std::endl;

  print_stack();

  std::cout <<std::endl << "After Running" << std::endl;
  compute_squares(a5,b5,8);
  print_stack();

  std::cout << "End of a Test" << std::endl << std::endl;
  
  clear_stack_labels();
  // End of a test case
/*
  // N is smaller than array length
  uintptr_t a2[] = {1,2,3,4,5,6,7,8};
  uintptr_t b2[] = {0,0,0,0,0,0,0,0};
  compute_squares(a2,b2,5);

  std::cout << "End of a Test" << std::endl << std::endl;
  print_stack();


  // B array is bigger -- leads to unused memory
  uintptr_t a3[] = {2,4,6,8};
  uintptr_t b3[] = {0,0,0,0,0,0};
  compute_squares(a3,b3,4);

  std::cout << "End of a Test" << std::endl << std::endl;
    print_stack();


  // N is bigger than array length --  Seg fault
  uintptr_t a4[] = {45,76,34};
  uintptr_t b4[] = {0,0,0};
  compute_squares(a4,b4,5);

  std::cout << "End of a Test" << std::endl << std::endl;
    print_stack();


  // B array is smaller -- leads to seg fault
  uintptr_t a5[] = {10,20,30,40,50,60};
  uintptr_t b5[] = {0,0,0,0};
  compute_squares(a5,b5,6);

  std::cout << "End of a Test" << std::endl << std::endl;
    print_stack();

*/
}

