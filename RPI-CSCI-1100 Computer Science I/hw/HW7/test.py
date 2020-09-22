"""
Description
"""

#Import Statements
import json

#Functions
def make_histogram(val_list):
    """
    
    """
    if not len(val_list)-val_list.count(-9999)<2:
        num = int(((sum(val_list)+(9999*val_list.count(-9999)))/(len(val_list)-val_list.count(-9999)))//1)
        out_string = "*"*num
    else:
        out_string = "Not enough data"    
    return out_string
    

def calculate_average(val_list):
    """
    Description
    """
    if not len(val_list)-val_list.count(-9999)<4:
        avg = round((sum(val_list)+(9999*val_list.count(-9999)))/(len(val_list)-val_list.count(-9999)),1)
    else:
        avg = "Not enough data"    
    return avg
def remove_bad_data(val_list):
    """
    Descripton
    """
    new_list = []
    for i in val_list:
        if not i[0]==-9999:
            new_list.append(i)
    return new_list

def calc_max(val_list):
    """
    Description
    """
    val_list.sort(reverse=True)
    #8: 92.0, 9: 88.0, 10: 83.0
    if not len(val_list)<4:
        out_string = "{}: {:.1f}, {}: {:.1f}, {}: {:.1f}".format(val_list[0][1], val_list[0][0], val_list[1][1], val_list[1][0], val_list[2][1], val_list[2][0])
    else:
        out_string = "Not enough data"
    return out_string

def calc_min(val_list):
    """
    
    """
    val_list.sort()
    #8: 92.0, 9: 88.0, 10: 83.0
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

MNTM = [-9999]*12

#Iterate through that year's months and add data
for i in range(start_point,end_point):
    EMXT.append((data[i]["EMXT"],data[i]["month"]))
    EMNT.append((data[i]["EMNT"],data[i]["month"]))
    DT90.append((data[i]["DT90"],data[i]["month"]))
    DX32.append((data[i]["DX32"],data[i]["month"]))
    TPCP.append((data[i]["TPCP"],data[i]["month"]))
    TSNW.append((data[i]["TSNW"],data[i]["month"]))
    
    if not data[i]["MNTM"]==-9999:
        MNTM[data[i]["month"]-1]=(data[i]["MNTM"])

#Remove all -9999 values from the lists
EMXT = remove_bad_data(EMXT)
EMNT = remove_bad_data(EMNT)
DT90 = remove_bad_data(DT90)
DX32 = remove_bad_data(DX32)
TPCP = remove_bad_data(TPCP)
TSNW = remove_bad_data(TSNW)

#Print out first parts of the output
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
print("Average temperatures")
print("-"*70)
print("Overall:",calculate_average(MNTM))
print("First 6 months:",calculate_average(MNTM[0:6:1]))
print("Last 6 months:",calculate_average(MNTM[6:len(MNTM):1]))
print("")
print("Temperature histograms")
print("-"*70)
print("01-03:",make_histogram(MNTM[0:3]))
print("04-06:",make_histogram(MNTM[3:6]))
print("07-09:",make_histogram(MNTM[6:9]))
print("10-12:",make_histogram(MNTM[9:12]))