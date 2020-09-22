HOMEWORK 6 CONTEST: INVERSE WORD SEARCH


NAME:  < Weston Jones >


OPTIMIZATIONS:
What did you do?

I submitted the same code for the HW and the contest. 

However, when completing the homework, I found that is was much more efficient to check a filled out
board for any forbidden words before adding it to a list of solutions rather than adding it without checking, then going back over
the list and removing boards. 


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




