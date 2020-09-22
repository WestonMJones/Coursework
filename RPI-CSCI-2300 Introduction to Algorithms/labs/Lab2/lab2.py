import math
import timeit
import random


   
def mult1(x, y):
    
    if x>y:
        bigger = x
        smaller = y
    else:
        bigger = y
        smaller = x
    
    bits = int.bit_length(bigger)
    result = 0
    
    for i in range(bits):
        mask = (1 << i)
        mask = (mask & smaller)
        result+=(bigger*mask)
    
    return result
    
        
def mult2(x,y):
    if y==0:
        return 0
    z = mult2(x,math.floor(y/2))
    
    if (y%2==0):
        return 2*z
    else:
        return (x + (2*z))

def mult3(x,y):
    n = max(int.bit_length(x),int.bit_length(y))
    if (n<=1):
        return x*y
    else:
        xl = (x>>math.floor(n/2))
        yl = (y>>math.floor(n/2))
        
        maskx = (1 << math.floor(n/2)) - 1
        masky = (1 << math.floor(n/2)) - 1
        
        xr = x & maskx
        yr = y & masky
        
        #print (x,"is x - split into",xl,"and",xr,"and",y,"is y - split into",yl,"and",yr)
        
        p1 = mult3(xl,yl)
        p2 = mult3(xr,yr)
        p3 = mult3(xl + xr, yl + yr)
        
        first = (p1 * pow(2, 2*math.floor(n/2)))
        second = ((p3-p1-p2) * pow(2,math.floor(n/2)))
        third = p2        
        
        
        return first + second + third
    
                
                
        
def randNum(num_digits):
    num = 0

    
    
    for x in range(num_digits):
        num += (random.randint(0,9) * pow(10,x))
    return num

#Main code
if __name__=='__main__':
    
    d = 1000
    
    x = randNum(d)
    y = randNum(d)
    t1 = []
    t2 = []
    t3 = []
    
    a1 = timeit.Timer("mult1(x,y)",globals=globals())
    a2 = timeit.Timer("mult2(x,y)",globals=globals())
    a3 = timeit.Timer("mult3(x,y)",globals=globals())
    
    print("x is",x,"and y is",y)
    
    for i in range(10):
        t1.append(a1.timeit(1))
        t2.append(a2.timeit(1))
        t3.append(a3.timeit(1))
        
    avg1 = sum(t1) / float(len(t1))
    avg2 = sum(t2) / float(len(t2))
    avg3 = sum(t3) / float(len(t3))
    
    print(avg1)
    print(avg2)
    print(avg3)
        
    
    
    
    
        

    
        
        
    
    
    
    
