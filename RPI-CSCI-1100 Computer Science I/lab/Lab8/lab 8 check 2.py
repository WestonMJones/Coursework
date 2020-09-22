def get_words(d):
    words = set()
    
    #(.,()")
    
    d=d.replace(".","")
    d=d.replace(",","")
    d=d.replace("(","")
    d=d.replace(")","")
    d=d.replace("\"","")
    
    d=d.lower()
    
    w_list = set()
    w_list = d.split()
    
    for word in w_list:
        if len(word)>=4 and word.isalpha()==True:
            words.add(word)
    
    return words

fname1 = input("Enter the first file name: ")
fname2 = input("Enter the second file name: ")

f = open(fname1)
s = f.read()
name1,description1 = s.split("|")

f = open(fname2)
s = f.read()
name2,description2 = s.split("|")

name1 = fname1.replace(".txt","")
name2 = fname2.replace(".txt","")

w1 = get_words(description1)
w2 = get_words(description2)

print("Comparing clubs",name1,"and",name2)
print("")
print("Same words:",w1&w2)
print("")
print("Unique to ",name1,": ",w1.difference(w2),sep="")
print("")
print("Unique to ",name2,": ",w2.difference(w1),sep="")
