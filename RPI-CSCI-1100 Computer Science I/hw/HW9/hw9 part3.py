"""
This program simulates a pokemon expoloration game
from text files
"""

#Import statements
import math

#Pokemon class
class Pokemon(object):
    def __init__( self, n, x0, y0, r0, h ):
        """
        Pokemon initialization method -- takes name, x position, y position and radius, and health
        """
        self.name = n
        self.x = int(x0)
        self.y = int(y0)
        self.radius = int(r0)
        self.health = int(h)

#Functions
def distance(x,y,pokemon):
    distance = math.sqrt((abs(x-pokemon.x)**2)+(abs(y-pokemon.y)**2))    
    return distance

#Main body
#Ask for user input
fname = input("File name => ")
print(fname)

#Load pokemon
count = 0
number_pokemon = 0
reading_pokemon = True
pokemon = []
for line in open(fname):
    if count==0:
        number_pokemon=int(line)
    else:
        
        if reading_pokemon:
            data = line.strip().split("|")
            data[4]=data[4].strip("\n")
            p = Pokemon(data[0],data[1],data[2],data[3],data[4])
            pokemon.append(p)
        else:
            break
        if count==number_pokemon:
            reading_pokemon=False
    count = count + 1

#Output pokemon
for p in pokemon:
    #Pichu: (10,10,5) Health: 2

    text = "{}: ({},{},{}) Health: {}".format(p.name,p.x,p.y,p.radius,p.health)
    text = text.rjust(12," ")
    print(text)

#Run other instructions
count = 0
trainers = dict()
print("")
for line in open(fname):
    if count>number_pokemon: #Check to see when pokemon list ends
        #Read line to get data
        data = line.strip().split("|")
        trainer = data[0]
        x = int(data[1])
        y = int(data[2].strip("\n"))
        
        #Throw pokeball
        #Make missed variable to determine if pokeball hit
        if len(pokemon)!=0:
            missed = True                            
            for p in pokemon:
                if distance(x,y,p)<p.radius:
                    #Loses 2 health
                    p.health=p.health-2
                    
                    #Check if caught
                    if p.health<0:
                        p.health=0
                    print("{} is caught!".format(p.name))
                    
                    #Add pokemon to trainer's list of catches
                    if trainer not in trainers.keys():
                        trainers[trainer] = []
                    trainers[trainer].append(p.name)
                    
                    #Remove pokemon from game
                    pokemon.remove(p)
                        

                    print("{} throws a pokeball to position ({}, {}) hits {}:".format(trainer,x,y,p.name))
                    text = "{}: ({},{},{}) Health: {}".format(p.name,p.x,p.y,p.radius,p.health)
                    text = text.rjust(12," ")
                    
                    missed = False
                elif distance(x,y,p)<p.radius+5:
                    #Loses 1 health
                    p.health=p.health-1
                    
                    #Check if caught
                    if p.health<0:
                        p.health=0
                    print("{} is caught!".format(p.name))
                    
                    #Add pokemon to trainer's list of catches
                    if trainer not in trainers.keys():
                        trainers[trainer] = []
                    trainers[trainer].append(p.name)
                    
                    #Remove pokemon from game
                    pokemon.remove(p)
                        

                    print("{} throws a pokeball to position ({}, {}) hits {}:".format(trainer,x,y,p.name))
                    text = "{}: ({},{},{}) Health: {}".format(p.name,p.x,p.y,p.radius,p.health)
                    text = text.rjust(12," ")  
                    missed = False
            if missed == True:
                print("{} misses at ({}, {})".format(trainer,x,y))  
    else:
        count = count+1
        

for trainer in sorted(list(trainers.keys())):
    print("{} caught {} pokemon".format(trainer,len(trainers[trainer])))
    for p in trainers[trainer]:
        print(p)
          