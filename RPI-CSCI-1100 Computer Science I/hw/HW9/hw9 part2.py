"""
This program searches for and displays yelp reviews for a business
"""

#Import Statements
import textwrap
import json

#Functions

#Mainbody
if __name__=='__main__':
    while True:
        #Get user input
        bizname = input("Enter a business name => ")
        print(bizname)
        
        #Load Json data from business file
        biznesses = dict()
        for line in open("businesses.json"):
            bizness = json.loads(line)
            if bizness["name"]==bizname:
                key = bizness["business_id"]
                data = bizness["full_address"]
                biznesses[key]=data
        
        #Get reviews
        reviews = dict()
        for line in open("reviews.json"):
            review = json.loads(line)
            key = review["business_id"]
            data = review["text"]
            if key in reviews.keys():
                reviews[key].append(data)
            else:
                reviews[key]=[data]
        
       
        choice = 0
        #Check # of locations
        if len(biznesses)==0:
            #No business by that name
            print("This business is not found")
            break
        elif len(biznesses)>1:
            #Multiple locations -- need to choose one
            print("")
            print("Found",bizname,"at:")
            print("")
            
            #Loop through biznesses dictionary to print address
            count = 1 #Make counter variable to enumerate list
            
            #Print addresses
            for key in (list(biznesses.keys())):
                print("{}.".format(count))
                print(biznesses[key])
                print("")
                count = count+1
            count = count-1
            #Ask for valid user selection
            choice = 0
            while choice<1 or choice>count:
                selectstr = "Select one from 1 - {} ==> ".format(count)
                choice = int(input(selectstr))
                print(choice)
        
        
        #With correct choice, assign business ID
        if choice == 0:
                choice=1    
        bizID = list(biznesses.keys())[choice-1]
       
     
        #Check if review present
        if not bizID in reviews.keys():
            #No reviews
            print("No reviews for this business are found")
        else:
            #Print reviews
            print("")
            print("Using",bizname,"at:")
            print(biznesses[bizID])
            
            count = 1
            for review in reviews[bizID]:
                print("Review: {}".format(count))
                wrapper = textwrap.TextWrapper( initial_indent = ' '*4, subsequent_indent = ' '*4 )
                message = review
                print(wrapper.fill(message))               
                count = count+1
                print("")
                print("")
                
            
            