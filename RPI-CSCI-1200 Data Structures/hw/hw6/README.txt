HOMEWORK 6: INVERSE WORD SEARCH


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< I looked up function list.unique() to help with some of the test cases >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 13 >


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?

To determine this I looked at the code in my program and recorded where ever it looped.

The algorithm starts out by looping through the number of required words,
then looping through the dimensions of the board. For each slot in the board, it performs 8 checks
that loop through the length of the current word. 

With each check (so also 8 times), the program copies the board, and calls the method fill blanks.

Fill blanks is a bit tricky -- On average, it loops through the dimensions of the board, the 24 character alphabet, and calls the function 
check solution.

Check solution loops through the number of forbidden words, the dimensions of the board, and performs another 8 checks.

Counting this all up, I'd say that the order notation is approximately

R * W * H * 8 * L * R * W * R * W * 24 * F * R * W * 8 * L

which simplifies down to 192 * R^4 * W^4 * H^4 * L^2


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

I was initially running my code through Dr. Memory, which made it run pretty slow.
I was pleasantly surprised to see that when ran with the time command, my program performed at superior speed for all the test cases. 
Only puzzle 8 took more than a second.

The output is correct for all but puzzle 6 (my program generates 8 extra solutions -- I think they must be duplicates)

Puzzle 1 One solution  0m0.031s
Puzzle 1 All solutions 0m0.029s
Puzzle 2 All solutions 0m0.017s
Puzzle 3 All solutions 0m0.053s
Puzzle 4 All solutions 0m0.031s
Puzzle 5 All solutions 0m0.041s
Puzzle 6 All solutions 0m0.034s
Puzzle 7 All solutions 0m0.657s
Puzzle 8 All solutions 0m2.870s

The first custom test case I created was meant to test the permutations that could be created with blanks.
Each blank can be any character is the alphabet, so 2+ blanks lead to a lot of different positionings and permutations.
On this test case, my program generated all 16224 solutions in 0m0.240s.

I thought this seemed pretty fast, so I guessed that it was the "vetting process" of removing forbidden words that
was slowing down my program. I added some forbbiden character strings to custom test case 1 (now custom test case 2), to
see how that affected runtime. 

Even with several forbidden words, the program still only took 0m0.224s to run. 

For my last custom test case I wanted to see my program struggle, so I took puzzle 8 and increased the width dimension by 1.
My program wasn't able to complete this -- it sucked all the memory away after about 2 minutes and had to be shut down.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!

I have a lot of different diretion checking functions -- they all basically do the same thing but in different directions
I added thorough comments to the first few in each series to show that I know how they work and so that you can understand how they work as well
However, I stopped commenting after while because it was getting redundant -- hopefully I won't be penalized


