HOMEWORK 1: AIRLINE SEATING


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
Piazza, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

-I didn't talk to/ask for help from any other students, TAs, or instructors.
-I compared outputs from the hidden testcase - Flight 301 Large -- with Madison Lawrence
-To generate the vector of the alphabet I modified some code I found on stack overflow
-To read and parse files, I used the methods from the data structures website that was linked in the homework pdf.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < about 7-8 >



EXPLANATION OF REMOVING PASSENGERS FROM UPGRADE LIST:
Describe the data structure you used to represent the upgrade lists,
and how you removed passengers from these lists.

I created a 2D Vector of strings -- upgrade_list -- holding the IDs of all the passengers scheduled for an upgrade.

If my SSR or SRN command failed to find a seat for a passenger, it would add them to the upgrade_list

The first vector of vectors was for those seeking an upgrade to first class and the second for those seeking an upgrade to bizness class

To remove a passenger, my CXL command parsed the vector of vectors. If the passenger_id parameter matched the value of an entry in the upgrade_list,
I changed that value to "NULL". Subsequent commands that dealt with the upgrade_list (UPP and UPL) I made skip over values that equalled "NULL"

To upgrade passengers I parsed the upgrade_list vector and called the SRN command for every item -- adding a parameter that would output a "passenger xxxx was upgraded" message if a seat was found and that would stop the command from adding the passenger back to the upgrade list if a seat was not found.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!


