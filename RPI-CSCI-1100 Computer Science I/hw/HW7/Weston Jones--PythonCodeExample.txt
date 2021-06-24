"""
This program reads data from a json file containing climate statistics for troy
and outputs that data in a more readable, visual form.
"""

#Import Statements
import json

#Functions
def make_histogram(val_list):
    """
    Given a list containing average monthly temperatures, this function returns
    a string that represents a histogram of that average or the text "Not enough data" if less than
    2 averages are found
    """
    if not len(val_list)-val_list.count(-9999)<2: #Account for the -9999 placeholders in the length calculation
        #Calculate the average over this period -- we have to account for the added sum and length of the -9999 placeholders
        num = int(((sum(val_list)+(9999*val_list.count(-9999)))/(len(val_list)-val_list.count(-9999)))//1)
        out_string = "*"*num
    #If less than 2 entries, return not enough data
    else: 
        out_string = "Not enough data"    
    return out_string
    
def calculate_average(val_list):
    """
    Given a list containing monthly temperatures, this function returns the average or "Not enough
    data if there are 3 or fewer entries to work with.
    """   
    if not len(val_list)-val_list.count(-9999)<4: #Account for the -9999 placeholders in the length calculation
        #Calculate the average over this period -- we have to account for the added sum and length of the -9999 placeholders        
        avg = round((sum(val_list)+(9999*val_list.count(-9999)))/(len(val_list)-val_list.count(-9999)),1)
    else:
        avg = "Not enough data"    
    return avg
def remove_bad_data(val_list):
    """
    This function removes all placeholder "-9999" values from a list of tuples containing
    climatic data and months (1-12)
    """
    #Create temporary list
    new_list = []
    #If the value isn't -9999, add it to the new list that is returned
    for i in val_list:
        if not i[0]==-9999:
            new_list.append(i)
    return new_list

def calc_max(val_list):
    """
    Given a list of tuples containing climatic data and associated months, this function
    calculates the maximum 3 climatic values and their associated months or returns
    "not enough data" if there are 3 or fewer values to work with.
    """
    val_list.sort(reverse=True)
    #Check length
    if not len(val_list)<4:
        out_string = "{}: {:.1f}, {}: {:.1f}, {}: {:.1f}".format(val_list[0][1], val_list[0][0], val_list[1][1], val_list[1][0], val_list[2][1], val_list[2][0])
    else:
        out_string = "Not enough data"
    return out_string

def calc_min(val_list):
    """
    Given a list of tuples containing climatic data and associated months, this function
    calculates the minimum 3 climatic values and their associated months or returns
    "not enough data" if there are 3 or fewer values to work with.
    """
    val_list.sort()
    #Check length
    if not len(val_list)<4:
        out_string = "{}: {:.1f}, {}: {:.1f}, {}: {:.1f}".format(val_list[0][1], val_list[0][0], val_list[1][1], val_list[1][0], val_list[2][1], val_list[2][0])
    else:
        out_string = "Not enough data"
    return out_string

#Main Body

#Load temperature data
data = json.loads(open("tempdata.json").read())

#Input Statement
in_year = int(input("Enter a year (1956-2015) => "))
print(in_year)

#Find first and last recorded month of that year in data

#Initialize variables that we'll need with placeholder values for now
start_point = -1
end_point = -1
counter = 0

for d in data:
    #Search for year
    if d["year"]==in_year:
        #Grab startpoint
        start_point = counter
        #Find endpoint -- If 2015 then just jump to the end of the data
        if in_year==2015:
            end_point=len(data)
        else:
            #If not 2015, keep incrementing until the year changes
            while data[counter]["year"]==in_year:
                counter=counter+1
            end_point = counter
        #Can end loop now that info has been found
        break
    else:
        counter = counter + 1
        
#Gather temperature and precipitation data

#Construct lists
EMXT = []
EMNT = []
DT90 = []
DX32 = []
TPCP = []
TSNW = []

#Construct average monthly temperature list with placeholder values
MNTM = [-9999]*12

#Iterate through that year's months and add data
for i in range(start_point,end_point):
    #Add data in the form of (value, month)
    EMXT.append((data[i]["EMXT"],data[i]["month"]))
    EMNT.append((data[i]["EMNT"],data[i]["month"]))
    DT90.append((data[i]["DT90"],data[i]["month"]))
    DX32.append((data[i]["DX32"],data[i]["month"]))
    TPCP.append((data[i]["TPCP"],data[i]["month"]))
    TSNW.append((data[i]["TSNW"],data[i]["month"]))
    
    #Add data to monthly average in integer rather than tuple (value, month) form
    #It will make things easier later on.
    if not data[i]["MNTM"]==-9999:
        MNTM[data[i]["month"]-1]=(data[i]["MNTM"])

#Remove all -9999 values from the lists except MNTM cuz we need to preserve the placeholders in that one
EMXT = remove_bad_data(EMXT)
EMNT = remove_bad_data(EMNT)
DT90 = remove_bad_data(DT90)
DX32 = remove_bad_data(DX32)
TPCP = remove_bad_data(TPCP)
TSNW = remove_bad_data(TSNW)

#Print out all the output

#Max and mins are easy -- just call the appropriate function
print("Temperatures")
print("-"*70)
print("Highest max value =>",calc_max(EMXT))
print("Lowest min value =>",calc_min(EMNT))
print("Highest days with max >= 90 =>",calc_max(DT90))
print("Highest days with max <= 32 =>",calc_max(DX32))
print("")
print("Precipitation")
print("-"*70)
print("Highest total =>",calc_max(TPCP))
print("Lowest total =>",calc_min(TPCP))
print("Highest snow depth =>",calc_max(TSNW))
print("Lowest snow depth =>",calc_min(TSNW))
print("")

#For average monthly temperatures, splice the average monthly temperature list
# and keep the placeholders so we an work on the first / last x months more easily
print("Average temperatures")
print("-"*70)
print("Overall:",calculate_average(MNTM))
print("First 6 months:",calculate_average(MNTM[0:6:1]))
print("Last 6 months:",calculate_average(MNTM[6:len(MNTM):1]))
print("")

#For histograms, splice the MNTM list for the desired range of averages
#See make_histogram function for more details
print("Temperature histograms")
print("-"*70)
print("01-03:",make_histogram(MNTM[0:3]))
print("04-06:",make_histogram(MNTM[3:6]))
print("07-09:",make_histogram(MNTM[6:9]))
print("10-12:",make_histogram(MNTM[9:12]))