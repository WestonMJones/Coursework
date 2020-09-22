"""
This program runs a number of user specified simulations -- 
each of 250 turns and records data about the simulations
"""

#imports
#-------------------------------------------------------------------------------
import random
import math

#functions
#-------------------------------------------------------------------------------

def run_one_simulation(grid):
    """
    runs the simulation and keeps track of the number of pokemon caught
    on each space in the grid. prob is the probability a pokemon will be caught
    at each turn
    """

    #Function Variables
    #-----------------#
    ptotal_sim = 0 #Total pokemon found in this instance of the sim
    pct = 0 #temporary variable to account for return statement in move_trainer 
    pos=(M//2,N//2) #set location of trainer to center of grid
    turn = 0 #Which turn this instance of the sim is on.
    
    #Sim loop
    while turn<250:
        pos,pct = move_trainer(pos,(M,N),p)

        #Handle pokemon
        if pct==1:
            grid[pos[0]][pos[1]]+=1 #Increment that location in the grid by 1
            ptotal_sim+=1 #ptotal_sim also gets incremented
        turn = turn + 1

    #Return # of pokemon caught and the new grid
    return ptotal_sim,grid

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

#variables and constants
#-------------------------------------------------------------------------------
M,N = 0,0 #Initialize variables for rows, columns. (This is in y,x format)
p = 0.0 #Decimal version of the probabily of finding a pokemon
pos = (0,0) #Rows, columns or M, N -- current position
ptotal = 0 #Total number of pokemon found in all simultions

#main body
#-------------------------------------------------------------------------------

#Input statements
M = int(input("Enter the integer number of rows => "))
print(M)

N = int(input("Enter the integer number of cols => "))
print(N)

p = float(input("Enter the probability of finding a pokemon (<= 1.0) => "))
print(p)

s = int(input("Enter the number of simulations to run => "))
print(s)

#Set up grid
count_grid = []
for i in range(M):
    count_grid.append( [0]*N )

# The grid is confusing so... visual
# M rows down
# Each row is N columns across
# M=2 and N=3
# [[0, 0, 0], [0, 0, 0]]

#Seed stuff
seed_value = 10*M + N
random.seed(seed_value)

#Run simulation

ptotal_sim=0 #Create temporary holder variable

simcount = 1 #keeps track of # of sim runs -- to be used for printing out
# which turn min / max occurs

#Min and Max variables
min_poke = math.inf #Minimum pokemon caught in simulation
max_poke = 0 #Maximum pokemon caught in simulation

s_min = 0 #Turn on which min value occurs
s_max = 0 #Turn on which max value occurs

while s>0:
    ptotal_sim,count_grid=run_one_simulation(count_grid)
    
    #Handle min and max stuff
    if ptotal_sim<min_poke:
        #If # of pokemon caught in last sim is less than current min
        min_poke=ptotal_sim
        s_min = simcount
    if ptotal_sim>max_poke:
        #If # of pokemon caught in last sim is more than current max       
        max_poke=ptotal_sim
        s_max = simcount
    
    #Get new total
    ptotal = ptotal + ptotal_sim
    
    #Advance loop and simcount
    s=s-1
    simcount+=1

#Output stuff
print("")

#Temporary string variables to get the grid spacing right
line = "" #Current row of the grid
temp = "" #Next thing to append to the line

#Output the grid
for x in range(M):
    for y in range(N):
        temp = "{:4d}".format(count_grid[x][y])
        line = line + temp
    print(line)
    line=""

#Account for divide by 0 errors
if s_max==0:
    s_max=1

print("")
print("Total pokemon caught is",ptotal)
print("Minimum pokemon caught was {} in simulation {}".format(min_poke,s_min))
print("Maximum pokemon caught was {} in simulation {}".format(max_poke,s_max))

#Calculate maximum on a space by storing maxes of each column-list in a new
#list then using the max function on that list
max_list = []
for i in count_grid:
    max_list.append(max(i))
max_space = max(max_list)

#Calculate minimum on a space by storing mins of each column-list in a new
#list then using the min function on that list
min_list = []
for i in count_grid:
    min_list.append(min(i))
min_space = min(min_list)

#Account for divide by zero errors
if ptotal==0:
    ptotal=1


if max_space==0 and min_space==0:
    #Adjusted code for if the simulation didn't return any pokemon
    print("Max number of pokemon caught on a space is {}".format(max_space))
    print("Min number of pokemon caught on a space is {}".format(min_space))    
else:
    #Normal code for when the simulation does return pokemon
    print("Max number of pokemon caught on a space is {} which was {:.2f}% of all pokemon caught".format(max_space,(max_space/ptotal)*100))
    print("Min number of pokemon caught on a space is {} which was {:.2f}% of all pokemon caught".format(min_space,(min_space/ptotal)*100))