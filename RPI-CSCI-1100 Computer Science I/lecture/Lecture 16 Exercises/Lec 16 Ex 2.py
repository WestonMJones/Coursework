fname = input("Enter the name of the IMDB file ==> ")
print(fname)

names = dict()
max_name = ""
max_val = 0

one_appearence_count=0

for line in open(fname, encoding = "ISO-8859-1"):
    #Parse line
    line.strip()
    a_line = line.split("|")
    name = a_line[0].strip()
    
    if name not in names:
        names[name]=1
    else:
        names[name]=names[name]+1
        if names[name]>max_val:
            max_val=names[name]
            max_name=name

for actor in names:
    if names[actor]==1:
        one_appearence_count+=1
        
print(max_name,"appears most often:",max_val,"times")
print(one_appearence_count,"people appear once")





    
