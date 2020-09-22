HOMEWORK 5: DSRADIO SONG GROUPS


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< I talked to a few ALAC tutors, but only briefly because they were hurrying through the queue >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < idk like 20 :( >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of s = the number of songs in the library,
g = the number of song groups, a = the average number of songs by the same 
artist, and l = the average length of song groups.

AddSongToLibrary O(s^2)

GroupExists O(g)

AddToGroup O(l)

MakeGroup O(g)

PrintGroupRewind O(l)

PrintLongestGroupRewind O(l*g)

RemoveGroup O(g)

DeleteAllSongGroups O(g*l)

RemoveFromGroup O(g*l) (the way I implemented it, but it could be O(1) if I had used getSongGroupPointer)

PrintGroupMarathon O(a)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

For debugging I mostly used Dr. Memory, print statements, and comparisons with the expected output.
For some of the harder bugs, I made use of some of the conditional breakpoint features in gdb.

I noticed that a lot of the submitty test cases tested corner cases (at least for RemoveFromGroup anyway),
so I verified my output with submity. Earlier on, I made my own input file that would test commands
as I programmed them. For example, after I made some of the print statements I'd test them on empty data structures, or
data structures that had had all elements removed from them.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

I didn't finish all the functions -- oops -- but luckily Submitty didn't
penalize me too heavily. If you see stuff missing, that's why.

