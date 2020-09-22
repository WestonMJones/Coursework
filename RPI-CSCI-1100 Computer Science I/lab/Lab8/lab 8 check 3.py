def get_words(d):
    words = set()
    
    #(.,()")
    
    d=d.replace(".","")
    d=d.replace(",","")
    d=d.replace("(","")
    d=d.replace(")","")
    d=d.replace("\"","")
    
    d=d.lower()
    
    w_list = {}
    w_list = d.split()
    
    for word in w_list:
        if len(word)>=4 and word.isalpha()==True:
            words.add(word)
    
    return words


fname = input("Please enter the name of a club: ")
f = open(fname)
s = f.read()
master_name,master_description = s.split("|")
master_words = get_words(master_description)

other_clubs = []

f = open('allclubs.txt')
for line in f:
    #Each line of all clubs
    club_name,club_description = line.split("|")
    
    if not club_name==master_name:
        club_words = get_words(club_description)
        
        n_common = len(master_words&club_words)
        other_clubs.append((n_common,club_name))
        

other_clubs.sort(reverse=True)
print("")
print("You should check out:")

for i in range(5):
    print(other_clubs[i][1],"-- it has",other_clubs[i][0],"similarities!")
    
        
        
        

        
    