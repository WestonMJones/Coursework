import lab05_util
import webbrowser

def print_info(restaurant):
    print(restaurant[0]," (",restaurant[5],")",sep="")
    address = restaurant[3].split("+")
    print(address[0])
    print(address[1])
    
    num_reviews = len(restaurant[6])
    
    if num_reviews<3:
        #Less than 3 reviews
        average = sum(restaurant[6])/num_reviews
        
    else:
        #More than 3 reviews -- drop max and min
        review_sum = sum(restaurant[6])
        review_sum = review_sum - max(restaurant[6])
        review_sum = review_sum - min(restaurant[6])
        
        average = (review_sum)/(num_reviews-2)

    if average>=0 and average<2:
        #0 to 2
        print("This restaurant is rated bad, based on",num_reviews,"reviews.")
    elif average>=2 and average<3:
        #2 to 3
        print("This restaurant is rated average, based on",num_reviews,"reviews.")
    elif average>=3 and average<4:
        #3 to 4
        print("This restaurant is rated above average, based on",num_reviews,"reviews.")
    elif average>=4 and average<5:
        #4 to 5
        print("This restaurant is rated very good, based on",num_reviews,"reviews.")
        
        
    
    
    
    
    print("")
    
    
    return

    



restaurants = lab05_util.read_yelp('yelp.txt')

text = "Input an ID from 1 to "+str(len(restaurants))+" ==> "

rest_id = int(input(text))

if rest_id>=0 and rest_id<=len(restaurants):
    #Valid ID
    print_info(restaurants[rest_id-1])
    
    print("What would you like to do next?")
    print("1. Visit the homepage")
    print("2. Show on Google Maps")
    print("3. Show directions to this restaurant")
    choice = int(input("Your choice (1-3)? ==> "))
    
    if choice==1:
        #1
        webbrowser.open(restaurants[rest_id-1][4])    
    elif choice==2:
        #2
        webbrowser.open("http://www.google.com/maps/place/"+restaurants[rest_id-1][3])
    elif choice==3:
        #3
        webbrowser.open("http://www.google.com/maps/dir/110 8th Street Troy NY/"+restaurants[rest_id-1][3])        
else:
    #BAd ID
    print("Enter a valid ID silly")


