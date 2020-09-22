HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 
I got this code: "static MTRand_int32 mtrand(time(NULL));" regarding use of the random number class
from an instructor's post on Piazza.
 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?

Memory Usage = O(M * P^W)

For the memory usage order notation, I looked at the map diagram in the pdf. Each entry in the outermost map is a unique word from the input text (M). Inside each entry in the first map is a number of other maps equal to the number of words following the first word (P). Those maps also branch off to a number of other maps that store repeated words, up to a number of times equal to the window size (W). Thus order notation is about O(M * P^W).

What is the order notation for performance (running time) of each of
the commands?

Load is O(N*log(M)^W) -- Reads through every line of the input file (N) and for every line it updates a number of dictionaries (log(M)) equal to the "depth" of the data structure (W)

Print is M^W -- Has to iterate through a number of maps that grows as the window size also grows. (This assumes the code is designed to handle window lengths of any size).

Generate is O(P) -- Iterates through the number of words that follow a particular word up to L times where L is the requested length of the string. L isn't included in our analysis though.


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).

:( Didn't attempt the extra credit.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


