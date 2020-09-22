"""
This program reads data from various textfiles and uses that data to run a short
"Angry birds" simulation. 
"""

#Import statements
from Pig import *
from Bird import *
from Barrier import *

#Functions
def out_of_bounds(bird):
    """
    Given a bird object, this function returns true if
    the bird is outside the bounds of the game field
    or false if it is in the bounds
    """
    #A bird has left the playing field if its x position minus its radius is less than 0 or its x position plus 
    #its radius is greater than 1000, or its y position
    #minus its radius is less than 0 or its y position plus its radius is greater than 1000
    if (bird.x-bird.radius)<0 or (bird.x+bird.radius)>1000 or (bird.y-bird.radius)<0 or (bird.y+bird.radius)>1000:
        return True
    else: 
        return False

#Main code
if __name__=='__main__':
    
    #Input statements
    bird_file = input("Enter the name of the bird file => ")
    print(bird_file)
    pig_file = input("Enter the name of the pig file => ")
    print(pig_file)
    barrier_file = input("Enter the name of the barrier file => ")
    print(barrier_file)
    
    #Create bird list
    birds = []
    
    #Parse data    
    for line in open(bird_file):
        data = line.strip().split("|")
        bird = Bird(data[0],data[1],data[2],data[3],data[4],data[5],data[6])
        birds.append(bird)
    
    #Create pig list
    pigs = []
    
    #Parse Data    
    for line in open(pig_file):
        data = line.strip().split("|")
        pig = Pig(data[0],data[1],data[2],data[3])
        pigs.append(pig)        
    
    #Create barrier list
    barriers = []
    
    #Parse Data
    for line in open(barrier_file):
        data = line.strip().split("|")
        barrier = Barrier(data[0],data[1],data[2],data[3],data[4])
        barriers.append(barrier)
    
    #Output initial set-up
    
    #Birds first
    print("")    
    print("There are {} birds:".format(len(birds)))
    for bird in birds:
        print("    {}: ({:.1f},{:.1f})".format(bird.name,bird.x,bird.y))
        
    #Now pigs
    print("")
    print("There are {} pigs:".format(len(pigs)))
    for pig in pigs:
        print("    {}: ({:.1f},{:.1f})".format(pig.name,pig.x,pig.y))
        
    #Finally, barriers
    print("")
    print("There are {} barriers:".format(len(barriers)))
    for barrier in barriers:
            print("    {}: ({:.1f},{:.1f})".format(barrier.name,barrier.x,barrier.y))    
    
    #Set loop variables
    turn = 0
    game_on = True #variable that controls the game's main loop
    new_bird = True #variable that controls when to print "starts at" message
    pigs_win = True #variable to determine which side wins
    
    #Begin simulation
    print("")    
    while game_on:            
        #Initial print statements
        if new_bird==True:
            print("Time {}: {} starts at {}".format(turn,birds[0].name,birds[0].position()))
            new_bird=False
        
        #Increment the time counter
        turn = turn + 1
        
        #Move the current bird by its dx and dy values
        birds[0].x+=birds[0].dx
        birds[0].y+=birds[0].dy
        
        #Check to see if the bird's circle intersects the circle of a pig that has not yet been popped.        
        # (Intersection occurs when the distance between the two circle centers is less than or equal to the sum of the two circle radii
        for pig in pigs:
            if birds[0].collided(pig):
                #If there was a collision pop the pig
                print("Time {}: {} at {} pops {}".format(turn,birds[0].name,birds[0].position(),pig.name))
                pigs.pop(pigs.index(pig))
                
                #Decrease bird speed by half 
                birds[0].dx*=.5
                print("Time {}: {} at {} has (dx, dy) = {}".format(turn,birds[0].name,birds[0].position(),birds[0].dx_and_dy()))
                
                #Condtions of the problem are such that no two pigs can be popped at once -- therefore safe to exit
                break
        
        #Check to see if the bird's circle intersects the circle of a barrier that has not yet crumbled.
        for barrier in barriers:
            if birds[0].collided(barrier):
                #Print one line giving the time, the name of the bird, the position of the bird, the name of the barrier and the barrier's strength  post collision. 
                barrier.calculate_damage(birds[0])
                print("Time {}: {} at {} hits {}, Strength {:.1f}".format(turn,birds[0].name,birds[0].position(),barrier.name,barrier.strength))

                #Set bird speed to 0
                birds[0].dx=0
                birds[0].dy=0                  

                #If the barrier's strength is dropped to 0, the barrier crumbles and an additional message is printed          
                if barrier.strength==0:
                    print("Time {}: {} crumbles".format(turn,barrier.name))
                    barriers.pop(barriers.index(barrier))
                    print("Time {}: {} at {} has (dx, dy) = {}".format(turn,birds[0].name,birds[0].position(),birds[0].dx_and_dy()))            
               
        #If the bird reaches a speed below MINSPEED==6, stop moving the bird, remove it from the simulation, and move on to the next bird.
        if len(birds)!=0 and birds[0].speed()<6: #Confirm there are still birds in play and check speed
            print("Time {}: {} at {} with speed {:.1f} stops".format(turn, birds[0].name,birds[0].position(),birds[0].speed()))
            birds.pop(0)
            new_bird=True
            
        #Check If any part of the bird's circle has gone outside the rectangle
        if len(birds)!=0 and out_of_bounds(birds[0]): #Confirm there are still birds in play and check bounds
            print("Time {}: {} at {} has left the game".format(turn,birds[0].name,birds[0].position()))
            birds.pop(0)
            new_bird=True
        
        #If all pigs are popped then output a message and stop the game
        if len(pigs)==0:
            print("Time {}: All pigs are popped. The birds win!".format(turn))
            break #End loop and the game
            
        #Otherwise, if there are no more birds, output a message with the names of the surviving pigs
        #(ordered by their order of input). and stop the game
        if len(birds)==0:
            print("Time {}: No more birds. The pigs win!".format(turn))
            print("Remaining pigs:")
            for pig in pigs:
                print(pig.name)
            break #End game