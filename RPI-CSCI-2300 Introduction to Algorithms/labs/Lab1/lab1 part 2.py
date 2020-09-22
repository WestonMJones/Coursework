import timeit
   
def fib2(n):
    if n==0:
        return 0
    elif n==1:
        return 1
    else:
        nums = [0, 1]
        for i in range(2,n+1):
            nums.append(nums[i-2]+nums[i-1])
        return nums[n]   
            

#Main code
if __name__=='__main__':
    
    t2 = timeit.Timer("fib2(n)",globals=globals())
    nvalues = [pow(2,10),pow(2,11),pow(2,12),pow(2,13),pow(2,14),pow(2,15),pow(2,16),pow(2,17),pow(2,18)]
    for n in nvalues :
        print(t2.timeit(1))
    
        
        
    
    
    
    
