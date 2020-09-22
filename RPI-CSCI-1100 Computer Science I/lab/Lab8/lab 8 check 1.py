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

#fname = "wrpi.txt"
fname = input("Enter file name: ")
f = open(fname)
s = f.read()
name,description = s.split("|")

output = get_words(description)
print("File",fname,len(output),"words")
print(output)

