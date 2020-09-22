import math
import random
   

def genArray(n):
    nextn = n
    count = 0
    while nextn>2:
        nextn = math.floor(math.sqrt(nextn))
        count=count+1
    print("Original n was:",n,"it took",count,"tries to get to:",nextn)
    return n
    
   
    
    
#Main code
if __name__=='__main__':
    
    for i in range(1,1001):
        i = i * 1005673490**i
        genArray(i)
        
      
        
   
   
   
   
   
    
    
    
            
            
        
    
        
    
    
    
        
    
        
        
    
    
    
    
