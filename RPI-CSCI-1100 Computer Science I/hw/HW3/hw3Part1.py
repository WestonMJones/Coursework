"""
This program displays information about the popularity of user input male
and female names for a given year.
"""

#imports
import read_names
import sys

#functions
def print_data(y,gender):
    print_line(y-10,gender)
    print_line(y-5,gender)
    print_line(y,gender)
    print_line(y+5,gender)
    print_line(y+10,gender)
 
def print_line(year,gender):
    #Check to see if year is within bounds
    if year>=1880 and year<=2014:
        (names,counts) = read_names.top_in_year(year, gender)
                       
        if name in names:
            # Name is found
            index = names.index(name)
            rank = index+1
            count = counts[index]
            percentage1 = (count/counts[0])*100
            percentage2 = (count/sum(counts))*100
            outstring = "   "+str(year)+": {:3d} {:5d} {:7.3f} {:7.3f}".format(rank,count,percentage1,percentage2)
            print(outstring) 
        else:
            # Name not found
            print("   ",year,": Not in the top 250",sep="")
            
#main body
read_names.read_from_file("top_names_1880_to_2014.txt")

y = int(input("Enter the year to check => "))
print(y)

if y<1880 or y>2014:
    #Checks for valid date
    print("Year must be at least 1880 and at most 2014")
    sys.exit()

#Ladies first
name = input("Enter a female name => ")
print(name)
print("Data about female names")
print(name,":",sep="")

print_data(y,"f")
print("")

#Now the dudes
name = input("Enter a male name => ")
print(name)
print("Data about male names")
print(name,":",sep="")

print_data(y,"m")


    
    
