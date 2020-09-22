HOMEWORK 8: B+ TREES


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 
I just used the demo website given in the HW pdf to simulate b+ trees 
I used the ds_set class and sample BFS code from the data structures website as reference too
>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

For testing the program I made use of print statements that would output the contents of every relevant node when a function
changed something in the tree.

I made my own function that would call a bunch of insert statements, run the code through Dr. Memory, then compare the output
step by step with the simulator referenced by the HW pdf.

For corner cases, I ended up creating a special case for when the root node is full and needs to be split for the first time.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

