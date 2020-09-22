HOMEWORK 2: LEAGUE OF LEGENDS CLASSES


NAME:  < Weston Jones >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
I got this chunk of code: "names.erase(std::unique(names.begin(), names.end()), names.end());" 
that I used to remove duplicates from a vector of strings from stack overflow.

I didn't talk to anyone about my code.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



DESCRIPTION OF 3RD STATISTIC: 
Please be clear & concise!  What is your hypothesis for the creation
of this statistic?

My stastic is a holistic "score" number that is assigned to each player.
 Kills are worth 10 points
 Assists are worth 2 points 
 Winning a match is worth 5 points
 A death is worth -4 points
 losing a match doesn't effect your score.

 The program looks at all the matches in a game and outputs a table of stats (score included)
 for every player. It's ranked by score (descending) and then lexicographically by player name.


RESULTS FROM 3RD STATISTIC:
Paste in a small amount of sample output into this file, or list the
file names of sample input & output included with your submisssion.
Describe what is interesting about your statistic on this data.
Please be concise!

PLACE   PLAYER NAME         SCORE   KILLS   DEATHS  KDR     ASSISTS WINS    LOSSES  
    1.  ERAQAQAQAR          46      5       1       5.00    0       0       1       
    2.  Yoreo               25      2       0       2.00    0       1       0       
    3.  XianJin             21      2       1       2.00    0       1       0       
    4.  SauceShooter        20      2       0       2.00    0       0       1       
    5.  EzXin               17      2       2       1.00    0       1       0       
    6.  Hebs                15      1       0       1.00    0       1       0       
    7.  Massacre10          15      1       0       1.00    0       1       0       
    8.  Bizu                13      2       3       0.67    0       1       0       
    9.  TheOneWhoHunts      12      2       2       1.00    0       0       1       
   10.  Ind0                6       1       1       1.00    0       0       1       
   11.  AquaNova            5       0       0       0.00    0       1       0       
   12.  JaxintheBox         5       0       0       0.00    0       1       0       
   13.  guardianForceX      5       0       0       0.00    0       1       0       
   14.  D0odleBob           0       0       0       0.00    0       0       1       
   15.  JrBatman            0       0       0       0.00    0       0       1       
   16.  RoofEooooH          -4      0       1       0.00    0       0       1       
   17.  TSMBumbus           -4      0       1       0.00    0       0       1       
   18.  DonMinator          -8      0       2       0.00    0       0       1       
   19.  LaKeA               -8      0       2       0.00    0       0       1       
   20.  ZeLLBaby            -11     0       4       0.00    0       1       0       


MISC. COMMENTS TO GRADER:  
Optional, please be concise!

