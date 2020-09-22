def Dict(word):
    if word=="it" or word=="was" or word=="the" or word=="best" or word=="of" or word=="times":
        return True
    else:
        return False
    
def prob2(string):
    
    string = "!" + string
    
    d = [False]*(len(string))
    c = [0]*len(string)
    d[0] = True
    
    for i in range(len(string)):
        for j in range(i):
            if (d[j]==True)and(Dict(string[j+1:i+1])==True):
                d[i]=True
                c[i]=j
                
    
    order = []
    i=len(string)-1
    while i>0:
        order.append(string[c[i]+1:i+1])
        i = c[i]
     
    order = list(reversed(order))
    print(order)
    return d[len(string)-1]

print(prob2("itwasthebestoftimes"))
#
        
                    
                
        
        
        
    
    