HOMEWORK 3: MATRIX CLASS


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< I used the vec.h files from lab 5 as a reference and copied a lot of the code from there (the destructor, copy constructor, and assignment operator) >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 hours >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

num_rows O(1)

get_column O(m^2) or O(n^2) if we use standard notaton

operator<< O(m*n) or O(n^2) if we use standard notation

quarter O(m*n) or O(n^2) if we use standard notation

operator== O(m*n) or O(n^2) if we use standard notation

operator!= O(m*n) or O(n^2) if we use standard notation

swap_rows O(n)

rref (provided in matrix_main.cpp)

O(m*m*n) or O(n^3) if we use standard notation



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?. 

I made extensive use of Dr. Memory for debugging this assignment.
 Everytime I implemented a function, I would
add various test cases to the student tests function and run the program through
Dr. Memory. I used the print function and the assert function to test the correctness of
the test cases and used Dr. Memory to find any memory errors.

I tested corner cases by testing each function in extreme scenarios (e.g. the
I used get and set on the corners of a matrix and tested functions on unitialized matrices)

EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

I tried, but it doesn't work.
It would have been O(n^2)



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

