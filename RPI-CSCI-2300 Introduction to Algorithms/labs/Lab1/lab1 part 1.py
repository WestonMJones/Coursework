import sys
import timeit


def fib1(n):
    if n==0:
        return 0
    elif n==1:
        return 1
    else:
        return (fib1(n-1) + fib1(n-2))
    
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
    
    t1 = timeit.Timer("fib1(n)",globals=globals())
    t2 = timeit.Timer("fib2(n)",globals=globals())
    nvalues = [1, 5, 10, 15, 20, 25, 30, 35, 40, 41, 42, 43]
    for n in nvalues :
        print("n=",n,"fib1=",fib1(n),"and fib2=",fib2(n))
        #print(n)
        #print(t1.timeit(1))
        #print(t2.timeit(1))
    
        
        
    
    
    
    
