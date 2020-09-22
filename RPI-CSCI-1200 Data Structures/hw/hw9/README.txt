HOMEWORK 9: MINIBLAST


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< 

I used the hash function from lecture 22 -- the implementation that came 
from http://www.partow.net/programming/hashfunctions/

>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7 >


HASH FUNCTION DESCRIPTION

The hash function I used came from Lecture 22 which in turn copied it from http://www.partow.net/programming/hashfunctions/

It loops through  the characters in the key and uses the bitwise XOR
and right and left shift operations on the current character to produce a somewhat random, large number.

I then added a line to the code that does hash = hash % max_size to ensure every generated index would fall within
the bounds of the table while perserving the random, uniform distribution. 

HASH TABLE IMPLEMENTATION

The hash table uses a vector of pairs where each pair contains a string (the kmer) and a vector of integers (the locations of that kmer in the genome)

For resize my program creates a copy of the current hash table vector, creates a new hash table vector of appropriate size, 
sets the new, empty vector to be the current hash table vector, then loops through the old vector copy and rehashes and inserts any non
empty indices into the new table.

I used a flag variable to indicate when the table is being resized so insert doesn't increment the current size of the hash table. 


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the map data structure require (order notation for memory use)?

I'll assuming that by "map data structure" the question means the vector/top level part of the hash table itself...

The vector has to store a number of unique keys of size k. 
The keys are substrings of the genome, but since they overlap, there should be about L-k in total. 

Therefore, order notation for memory use is (L-K)*K

If by "map data structure" the question is referring to the entire hash table class I wrote,
it's memory use would be L + (L-k)*k because my class also stores the genome as a string.

What is the order notation for performance (running time) of each of
the commands?

Genome command - O(L*k)
-------------------------------------------------------------------------------
The command has to parse the genome string character by character, so that's an operation
of order L. For each character in the genome string, the command calls the insert algorithm.
However, on average an insertion won't result in a collision or a resize, so it's just O(k).

I know hash functions are supposed to have O(1) inserts, but my hash function loops through the characters of the key, so it's technically O(k).
However, since kmer values tend to be pretty small, it shouldn't effect performance too much. 

Table_size, occupancy, kmer - All O(1)
-------------------------------------------------------------------------------
My program just assigns a variable a value with these commands.  

Query - O(k + p*q)
-------------------------------------------------------------------------------
First query has to get a string of length equal to the kmer size from the query string.
This is a loop up to kmer size spaces in the query string -- so an order K command.

With the kmer, the command now has to look up that key in the table which is on average an O(k) operation.

Once the index is found, the command loops through the number of different locations where the key/kmer is found in the genome (order p).

For each different location, the command loops through the characters of the query string and compares them to the relevant index 
in the genome file. Each of those loops is equal to the length of the query, so they're order q operations.

Order notation should be K + P*Q. K is a constant because we only need to extract the key of length k from the query + call the hash function once.
From there the command uses nested for loops that loop through the length of the number of different locations and query size, respectively.
-------------------------------------------------------------------------------- 

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


