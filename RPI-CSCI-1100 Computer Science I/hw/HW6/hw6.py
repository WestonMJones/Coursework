"""
This program plays the six degrees of separation / Kevin Bacon game
with Dr. Who villains. It reads a list of villains and their episode appearences
from a file, then guides the user from the game by prompting them for selections
"""
#No import statements :(

#Functions
def parse_line(line):
    """
    Given a line of text straight from the textfile, this function
    parses the line and returns (# of appearences, name of villian, set of show titles
    in tuple form. Extra whitespace is removed and titles follow standard capitalization rules
    """
    
    #Initial split by tab character
    data = line.split("\t")
    
    #Handle the villain name
    name = data[0].strip()
    
    #Fill the show titles set and remove any extra space + keep capitalization standard
    
    #data[7]=data[7].replace("/",",") #HW instructions lied >:( -- "/"s can also separate titles, so account for that
    #data[7]=data[7].replace("(also see Alliance above)","") #titles also sometimes have parenthetical qualifiers
    #Nvm, the program doesn't work if we do that -- just assume all commas
 
    shows = set()
    temp = data[7].strip().split(",")

    for i in range(len(temp)):
        temp[i]=temp[i].strip().lower().title()
        shows.add(temp[i])
    
    #Handle the number of appearences
    number = len(shows)
    
    #Final return statement
    return (number,name,shows)

#Global Variables
villains = [] #List of tuples that contains all the villains and their attributes
candidates = [] #List of the villain tuples that are the current choices in the game
game_on = True #Tells loops when to stop
count = 1 #Variable that holds number of steps
str_choice = False #Variable that determine whether or not a user's selection is an integer and can be worked on

#Main Body

#Read the villains file and load it into the villains list
for line in open("DrWhoVillains.tsv"):
    villains.append(parse_line(line))

#Remove first entry (column headers)
villains.pop(0)

#Input statement
target = input("Who are you trying to reach? ")
print(target)
target = target.lower().title()
compare_target = target.lower()

#Sort villains
villains.sort(reverse=True)

#Start candidates list
for i in range(10):
    candidates.append(villains[i])

#Begin main loop
while game_on:
    #Display candidate villains
    print("")
    for i in range(len(candidates)):
        print("{}. {}".format(i+1,candidates[i][1]))
    
    #Ask for selection
    choice = input("Enter a selection => ")
    print(choice)
    
    #Handle non integer input
    if choice.isdigit():        
        temp=int(choice)
        choice = temp
        choice = choice - 1
        str_choice=False
    else:
        str_choice=True
    
    
    #Determine validity of selection
    if str_choice==True or choice<0 or choice>(len(candidates)-1):
        #Bad selection
        continue
    else:
        #Okay selection
        #Now check if selection is target villain
        print("")
        
        compare_name=candidates[choice][1].lower()
        
        if compare_target==compare_name:
            #Is target villain
            print("You reached the villain",target,"in",count,"steps.")
            print("Have a nice day.")
            game_on=False #End main loop
        else:
            #Not target villain, continue
            
            #Check number of appearences for proper grammar then output # of appearences
            if not candidates[choice][0]==1:
                print("{} appeared in {} stories and overlapped with:".format(candidates[choice][1],candidates[choice][0]))
            else:
                print("{} appeared in {} story and overlapped with:".format(candidates[choice][1],candidates[choice][0]))
            
            #Update candidates list
            search_set = set()
            search_set = candidates[choice][2]
            
            search_name = candidates[choice][1]
            
            candidates = [] #clear old candidates list
            
            for v in villains:
                temp = search_set&v[2]
                if len(temp)>0 and v[1]!=search_name:
                    candidates.append(v)
            
            candidates.sort(reverse=True)
            count = count+1 #Increment # of turns