import math
import timeit
import random
   
def modexp(x,y,n):
    if y==0:
        return 1
    else:
        z = modexp(x,math.floor(y/2),n)
        if (y%2==0):
            return (pow(z,2)%n)
        else:
            return (x*(pow(z,2))%n)

def test(n,k):
    tests = []

    first_msg = "When k=" + str(k) + " " + str(n) + " " 
    
    for i in range(k):
        tests.append(random.randint(1,n-1))
    for i in range(len(tests)):
        if (modexp(tests[i],n-1,n)!=1):
            print(first_msg + "is not prime")
            return False
    print(first_msg + "is prime")
    return True


#Main code
if __name__=='__main__':
    
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
              43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
              101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 
              151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199]
    
    nonprimes = [4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 
                 25, 26, 27, 28, 30, 32, 33, 34, 35, 36, 38, 39, 40, 
                 42, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57, 
                 58, 60, 62, 63, 64, 65, 66, 68, 69, 70, 72, 74, 75, 
                 76, 77, 78, 80, 81,82, 84, 85, 86, 87, 88, 90, 91, 
                 92, 93, 94, 95, 96, 98, 99, 100]
    
    carmichaels = [561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 
                  29341, 41041, 46657, 52633, 62745, 63973, 75361, 101101,
                  115921, 126217, 162401, 172081, 188461, 252601, 278545, 
                  294409, 314821, 334153, 340561, 399001, 410041, 449065, 
                  488881]
    
    print("Testing algorithm on prime numbers! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
    for i in range(len(primes)):
        print("")
        for k in range(1,10):
            test(primes[i],k)
           
    print("\nTesting algorithm on composite numbers! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
    for i in range(len(nonprimes)):
            print("")
            for k in range(1,10):
                test(nonprimes[i],k) 
            
    print("\nNow the Carmichael numbers! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
    for i in range(len(carmichaels)):
        print("")
        for k in range(1,10):
            test(carmichaels[i],k)
        test(carmichaels[i],1000)
            
            
        
    
        
    
    
    
        
    
        
        
    
    
    
    
