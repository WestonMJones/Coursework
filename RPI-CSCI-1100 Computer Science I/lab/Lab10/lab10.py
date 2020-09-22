import random
import time

def closest1(l):
    '''
    >>> closest1( [ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (5.4, 4.3)
    >>> closest1([ 18.3, 14.5, 7.3, 4.5, 2.9, 11.36, 5.93, 4.86 ])
    (4.86, 4.5)
    >>> closest1([-5,-7,4.5,8.5,9.3,9.3,85,73] )
    (9.3, 9.3)
    >>> closest1([-1,10] )
    (10, -1)
    >>> closest1([10,-1] )
    (10, -1)
    >>> closest1([3])
    (None, None)
    '''
    if len(l)<2:
        return (None, None)
    else:
        first_number = l[0]
        second_number = l[1]
        smallest_difference = abs(l[0]-l[1])
        
        for x in range(len(l)):
            for y in range(len(l)):
                if not y==x:
                    if abs(l[x]-l[y])<smallest_difference:
                        smallest_difference = abs(l[x]-l[y])
                        first_number = l[x]
                        second_number = l[y]
        output = [first_number, second_number]
        output.sort(reverse=True)
        return (output[0],output[1])
        
    
def closest2(l):
    '''
    >>> closest2( [ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (5.4, 4.3)
    >>> closest2([ 18.3, 14.5, 7.3, 4.5, 2.9, 11.36, 5.93, 4.86 ])
    (4.86, 4.5)
    >>> closest2([-5,-7,4.5,8.5,9.3,9.3,85,73] )
    (9.3, 9.3)
    >>> closest2([-1,10] )
    (10, -1)
    >>> closest2([10,-1] )
    (10, -1)
    >>> closest2([3])
    (None, None)
    '''    
    if len(l)<2:
        return (None, None)
    
    l2 = sorted(l)
    first_number = l[0]
    second_number = l[1]
    difference = abs(l[0]-l[1])
    
    for i in range(len(l2)-1,0,-1):
        if l2[i]-l2[i-1]<difference:
            difference = l2[i]-l2[i-1]
            first_number = l2[i]
            second_number = l2[i-1]
    output = [first_number, second_number]
    output.sort(reverse=True)
    return (output[0],output[1])
        
if __name__ == "__main__":
    
    l100 = []
    for i in range(0,100):
        l100.append(random.uniform(0.0, 1000.0))
    
    print("100 number list generated")    
    
    l1000 = []
    for i in range(0,1000):
        l1000.append(random.uniform(0.0, 1000.0))
        
    print("1,000 number list generated")
        
    l10000 = []
    for i in range(0,10000):
        l10000.append(random.uniform(0.0, 1000.0))
        
    print("10,000 number list generated")
    
    print("")
    
    print("Testing first function")
    print("--------------------------------------------------")
    print("List with 100 values")
    start = time.time()
    nums = closest1(l100)
    end = time.time() - start
    print("Returned {} in {:.7f} seconds".format(nums,end))
    
    print("")
    print("List with 1000 values")
    start = time.time()
    nums = closest1(l1000)
    end = time.time() - start
    print("Returned {} in {:.7f} seconds".format(nums,end))
    
    print("")
    print("List with 10000 values")
    start = time.time()
    nums = closest1(l10000)
    end = time.time() - start
    print("Returned {} in {:.7f} seconds".format(nums,end))
    
    print("")
    print("Testing second function")
    print("--------------------------------------------------")    
    print("List with 100 values")
    start = time.time()
    nums = closest2(l100)
    end = time.time() - start
    print("Returned {} in {:.7f} seconds".format(nums,end))
    
    print("")
    print("List with 1000 values")
    start = time.time()
    nums = closest2(l1000)
    end = time.time() - start
    print("Returned {} in {:.7f} seconds".format(nums,end))
    
    print("")
    print("List with 10000 values")
    start = time.time()
    nums = closest2(l10000)
    end = time.time() - start
    print("Returned {} in {:.7f} seconds".format(nums,end))       
    