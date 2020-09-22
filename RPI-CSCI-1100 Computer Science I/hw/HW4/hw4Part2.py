"""
This program compares the death rate in two
user input New York neighborhoods and outputs the 
"nicer" of the two.
"""

#import statements
import hw4_util
import sys

#function statements
def pass_judgement(trendline,area1,area2):
    #Given the final trendline and the two
    #user input names, this function
    #compares the two death rates and returns the healthier area
    
    output=""
    
    if trendline.count("+")>trendline.count("-"):
        #First area is better
        output = "I would rather live in {} than {}".format(area1,area2)
        return output
    elif trendline.count("+")<trendline.count("-"):
        #Second area is better
        output = "I would rather live in {} than {}".format(area2,area1)
        return output
    else:
        #Both areas are the same
        output = "{} and {} are the same".format(area1,area2)
        return output

#main body

#Handle the first name and data set
name1 = input("Enter the first area to check => ")
print(name1)
cdata1 = hw4_util.read_deaths(name1)
if len(cdata1)==0:
    #check name validity
    print(name1,"is an invalid name")
    sys.exit()

#Handle the second name and data set
name2 = input("Enter the second area to check => ")
print(name2)
cdata2 = hw4_util.read_deaths(name2)
if len(cdata2)==0:
    #check name validity
    print(name2,"is an invalid name")
    sys.exit()
    
#Compute the difference
list_difference = []
for i in range(0,11):
    list_difference.append(round(cdata1[i]-cdata2[i],1))

#Print header
print("")
print("       2013   2003")

#generate trend line
trend = ""
for i in range(10,-1,-1):
    if list_difference[i]>50:
        trend=trend+"-"
    elif list_difference[i]<-50:
        trend=trend+"+"
    else:
        trend=trend+"="

#Print trendline and the healthier area
print("Trend:",trend)
print("")
print(pass_judgement(trend,name1,name2))