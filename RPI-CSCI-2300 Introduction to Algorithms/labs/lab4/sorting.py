import math
import random
   
def genArray(n):
   num_list = []
    
   for i in range(n):
      num_list.append(random.randint(-5,n-1))
   return num_list

def sort(unsorted):
   
   min_val = min(unsorted)
   r = (max(unsorted) - min_val)+1
   count = [0] * r
   output = [0] * len(unsorted)
   
   for i in range(len(unsorted)):
      count[unsorted[i]-min_val]+=1
   
   total = 0
   for i in range(r):
      previous = count[i]
      count[i] = total
      total += previous
      
   for i in range(len(unsorted)):
      output[count[unsorted[i]-min_val]]=unsorted[i]
      count[unsorted[i]-min_val]+=1   
      
   return output
    
#Main code
if __name__=='__main__':
   
   for i in range(1,11):
      print("\nTest #1 when i =",i)
      arr = genArray(i)
      print("Unsorted array is:",arr)
      arr = sort(arr)
      print("Sorted array is:",arr)
      
      print("\nTest #2 when i =",i)
      arr = genArray(i)
      print("Unsorted array is:",arr)
      arr = sort(arr)
      print("Sorted array is:",arr)      
      
      print("\nTest #3 when i =",i)
      arr = genArray(i)
      print("Unsorted array is:",arr)
      arr = sort(arr)
      print("Sorted array is:",arr)        

   
   
   
   
   
   
    
    
    
            
            
        
    
        
    
    
    
        
    
        
        
    
    
    
    
