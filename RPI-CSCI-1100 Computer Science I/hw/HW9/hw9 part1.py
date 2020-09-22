"""
This program searches for businesses in a specified category
"""

#import statements
import json

#Functions 

#Main body
if __name__=='__main__':
    while True:
          
        data = dict()
    
        category = input("Enter a category ==> ")
        print(category)
        cutoff = int(input("Cutoff for displaying categories => "))
        print(cutoff)

    
        for line in open("businesses.json"):
            business = json.loads(line)
            if category in business["categories"]:
                for cat in business["categories"]:
                    if not cat==category:
                        if not cat in data.keys():
                            data[cat]=1
                        else:
                            data[cat]+=1
        if len(data)==0:
            print("Searched category is not found")
            break
    
    
    
        dlist = []
        for cat in data.keys():
            if data[cat]>=cutoff:
                dlist.append((cat, data[cat]))
        dlist.sort()
    
        print("Categories co-occurring with {}:".format(category))
    
        if len(dlist)==0:
            print("None above the cutoff")
            break
        
        for entry in dlist:
            str1 = "{}: {}".format(entry[0],entry[1])
            str1 = str1.rjust(30)
            print(str1)
        break