"""
Given a list of lego blocks, this program tells a user how many
of a certain type of block is available -- taking into account the ability to combine
multiple legos of one type into a new type.
"""

#imports
import hw3_util
import sys

#functions
def print_output(num_1x1,num_2x1,num_2x2,num_2x4):
    total_possible = num_1x1+num_2x1+num_2x2+num_2x4
    print("I can make",total_possible,lego_type,"pieces:")
    print("    ",num_2x4,"pieces of",lego_type,"using 2x4 pieces.")
    print("    ",num_2x2,"pieces of",lego_type,"using 2x2 pieces.")
    print("    ",num_2x1,"pieces of",lego_type,"using 2x1 pieces.")
    print("    ",num_1x1,"pieces of",lego_type,"using 1x1 pieces.")

#Main body
legos = hw3_util.read_legos('legos.txt')

total_1x1 = legos.count("1x1")
total_2x1 = legos.count("2x1")
total_2x2 = legos.count("2x2")
total_2x4 = legos.count("2x4")


lego_type = input("What type of lego do you need? ==> ")
print(lego_type)
print("")

if lego_type=="1x1":
    #1x1 is chosen
    print_output(total_1x1,0,0,0)
    
elif lego_type=="2x1":
    #2x1 is chosen
    print_output(total_1x1//2,total_2x1,0,0)
    
elif lego_type=="2x2":
    #2x2 is chosen
    print_output(total_1x1//4,total_2x1//2,total_2x2,0)
elif lego_type=="2x4":
    #2x4 is chosen
    print_output(total_1x1//8,total_2x1//4,total_2x2//2,total_2x4)
else:
    #illegal type
    print("Illegal lego")
    sys.exit()






