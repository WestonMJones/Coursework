"""
This program runs a simulation of a pokemon trainer in the middle
of a user specified rectangle. Movement is random as is the chance of catching
a pokemon.
"""

#import statements
import random

#functions
#-------------------------------------------------------------------------
def move_trainer( position, bounds, prob):
    """
    position is the current (row, col) position of the trainer, passed as a tuple
    bounds is the max (rows, cols) on the grid, again as a tuple
    prob is the probability p that a pokemon will be found at the current position
    """ 
    
    #rows = y and cols = x
    row = position[0]
    col = position[1]
    
    #Calculate move
    d = random.randint(0, 3)
    if d==0:
        #Move North
        row = row - 1
    elif d==1:
        #Move South
        row = row + 1
    elif d==2:
        #Moves East
        col = col + 1
    elif d==3:
        #Moves West
        col = col - 1
    
    #Check bounds
    if row<0: #If too far up
        row=0
    elif row>(bounds[0]-1): #if too far down
        row=bounds[0]-1    
    elif col<0: #if too far left
        col=0
    elif col>(bounds[1]-1): #if too far right
        col=bounds[1]-1
    
    #handle pokemon finding
    pokemon_found = 0     
    rand_num = random.random()
    if rand_num < prob:
        #Pokemon is found
        pokemon_found = 1
    return (row, col),pokemon_found


def report():
    #Outputs a line of info about the sims progress 
    #to be used every 20 turns
    print("Time step {}: position {} pokemon caught since the last report {}".format(turn,pos,pc))

#variables
#-------------------------------------------------------------------------

#Max number of rows
M = 0

#Max number of columns
N = 0

#Probability of finding a pokemon
p = 0.0

#Current coordinates of the trainer 
pos = (0,0) #Rows, columns or M, N

#Current turn count
turn = 1

#Total, Actual, and Temporary Pokemon count
ptotal = 0 #Total pokemon found
pc = 0 #pokemon found since last report
pct = 0 #temporary variable because the move_trainer function 
#instructions force us to return a 1 or 0 depending on whether or not a pokemon
# is found >:(

#main body

#input statements
M = int(input("Enter the integer number of rows => "))
print(M)

N = int(input("Enter the integer number of cols => "))
print(N)

p = float(input("Enter the probability of finding a pokemon (<= 1.0) => "))
print(p)

#Determine current pos
pos=(M//2,N//2)

#Seed stuff
seed_value = 10*M + N
random.seed(seed_value)    

#Main loop
while turn<=250:
    pos,pct = move_trainer(pos,(M,N),p)
    pc = pc + pct #pc gets incremented if a 1 is returned
    ptotal = ptotal + pct #ptotal also gets incremented
    if turn%20==0:
        #Generate report
        report()
        pc=0 #reset pokemon per report counter
    turn = turn + 1

#Once sim ends, execute last line to print closing message
print("After {} time steps the trainer ended at position {} with {} pokemon.".format(turn-1,pos,ptotal))
    
    