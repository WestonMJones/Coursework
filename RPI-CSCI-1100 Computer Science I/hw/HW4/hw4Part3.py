"""
This program simulates a virtual space with a user
controlled pokemon trainer that can capture pokemon
by walking over them
"""

#import statements
import hw4_util
import sys

#functions statements
def move_north(pos):
    return check_bounds(pos[0],pos[1]-1)

def move_east(pos):
    return check_bounds(pos[0]+1,pos[1])

def move_south(pos):
    return check_bounds(pos[0],pos[1]+1)

def move_west(pos):
    return check_bounds(pos[0]-1,pos[1])

def check_bounds(x,y):
    #stops the trainer from crossing the boundaries of the map
    if x>10:
        x=10
    elif x<0:
        x=0
    elif y>10:
        y=10
    elif y<0:
        y=0 
    return (x,y)

def print_pokemon():
    #Prints the list of non captured pokemon
    print("Current pokemon:")
    for i in range(0,len(pokemon)):
        print("    ",pokemon[i],"at",locations[i])
    print("")
    return

def print_loc():
    #prints the current location of the trainer
    print("Currently at",current_pos)
    return

def check_pokemon():
    #Checks to see if a pokemon is caught then
    #removes it from the list
    
    #create temporary index holder because deleting a list
    #value mid loop will mess things up
    index = -1
    
    #Check for any pokemon and output caught message
    for i in range(0,len(locations)):
        if locations[i]==current_pos:
            print("You capture a",pokemon[i],"on turn",turn)
            index = i
            
    #If pokemon found, delete it from list
    if not index==-1:
        pokemon.remove(pokemon[index])
        locations.remove(locations[index])
        index=0



#Variables
current_pos=(5,5)
pokemon, locations = hw4_util.read_pokemon()
end = False
turn = -1

#Main body
print_pokemon()

#Main loop
while end==False:
    cmd = input("N,S,E,W to move, 'print' to list, or 'end' to stop ==> ")
    print(cmd)
    
    cmd = cmd.lower()
    if cmd=="n":
        #Move north
        current_pos=move_north(current_pos)
        
    elif cmd=="s":
        #Move south
        current_pos=move_south(current_pos)
        
    elif cmd=="e":
        #Move east
        current_pos=move_east(current_pos)
        
    elif cmd=="w":
        #Move west
        current_pos=move_west(current_pos)
        
    elif cmd=="print":
        #print command
        print_pokemon()
        
    elif cmd=="end":
        #end command
        sys.exit()
    
    #Increment turn count
    turn = turn + 1
    
    #output location after any moves
    print_loc()
    
    #Check for any pokemon caught
    check_pokemon()