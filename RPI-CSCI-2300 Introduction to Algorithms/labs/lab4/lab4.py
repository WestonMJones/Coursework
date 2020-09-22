import math
import random
   
def select(array, k):
   sl = []
   sv = []
   sr = []
   
   if (len(array)==1):
      return array[0]
   else:
      v_index = random.randint(0,len(array)-1)

   v = array[v_index]
   
   for i in range(len(array)):
      if (array[i] < v):
         sl.append(array[i])
      elif (array[i] > v):
         sr.append(array[i])
      else:
         sv.append(array[i])

   if (k <= len(sl)):
      return select(sl,k)
   elif ((len(sl) < k)&(k<=(len(sl)+len(sv)))):
      return v
   elif (k>(len(sl)+len(sv))):
      return select(sr,((k-len(sl))-len(sv)))
   else:
      print("lolwut")
      return False
    
def genArray(n):
   num_list = []
    
   for i in range(n):
      num_list.append(random.randint(0,n-1))
   return num_list
    
    
#Main code
if __name__=='__main__':
      
   #array = [5, 8, 9, 5, 0, 0, 1, 7, 6, 9]
   
   #print("Testing on practice list:")
   #print("[0, 0, 1, 5, 5, 6, 7, 8, 9, 9]")
   
   #for k in range(1,11):
      #print("When k is:",k,"select returns:",select(array,k))
      
   #print("")
   #print("Testing on large values:")
   
   
   #for i in range(5):
      #n = random.randint(100,1000)
      #array = genArray(n)
      #print("\nRandomly generated list number:",i+1)
      #for k in range(1,11):
         #print("When k is:",k,"select returns:",select(array,k))
         #k = math.ceil((k*3434.5)%n)
         #print("When k is:",k,"select returns:",select(array,k))
      
         
   #print("")
   #print("Instruction Specified Case")
   
   
   k = 5
   n = random.randint(1,50)
   array = genArray(n)  
   
   array.sort()
   
   print("When k is:",k,"select returns:",select(array,k))
   
   
   for i in range(len(array)):
      print(array[i])
      
   
   
   
   
   
    
    
    
            
            
        
    
        
    
    
    
        
    
        
        
    
    
    
    
