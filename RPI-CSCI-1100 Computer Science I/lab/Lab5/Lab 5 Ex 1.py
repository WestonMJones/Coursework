import lab05_util

def print_info(restaurant):
    print(restaurant[0]," (",restaurant[5],")",sep="")
    address = restaurant[3].split("+")
    print("\t",address[0])
    print("\t",address[1])
    average = round(sum(restaurant[6])/len(restaurant[6]),2)
    print("Average Score:",average)
    print("")
    

    



restaurants = lab05_util.read_yelp('yelp.txt')
print_info(restaurants[0])
print_info(restaurants[4])

#["Meka's Lounge", 42.74, -73.69, '407 River Street+Troy, NY 12180', 'http://www.yelp.com/biz/mekas-lounge-troy', 'Bars', [5, 2, 4, 4, 3, 4, 5]]

#Meka's Lounge (Bars)
#407 River Street
#Troy, NY 12180
#Average Score: 3.86