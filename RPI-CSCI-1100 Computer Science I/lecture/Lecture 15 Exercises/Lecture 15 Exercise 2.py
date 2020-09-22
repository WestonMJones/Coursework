#Inputs
fname = input("Data file name: ")
print(fname)
pref = input("Prefix: ")
print(pref)

#Vars
num_lnames = 0
all_lnames = set()

for line in open(fname, encoding = "ISO-8859-1"):
    #Parse line
    line.strip()
    a_line = line.split("|")
    #Extract lastname from Line
    a_line[0].strip()
    name = a_line[0].split(",")
    lname=name[0].strip()
    
    #Add to list (or not)
    if not lname in all_lnames:
        all_lnames.add(lname)
        
        temp = lname[0:len(pref):]
        if temp==pref:
            num_lnames=num_lnames+1

print(len(all_lnames),"last names")
print(num_lnames,"start with",pref)