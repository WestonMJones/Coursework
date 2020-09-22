
# This method takes X, the array of coin denominations, and v the value to be equalled by the set of coins
def make_change(X,v):
    
    # Intialize the array C
    C = [False]*(v+1)
    
    # Handle the base case
    C[0] = True
    
    # Loop up until the max value
    # Move range up by 1 to handle the base case
    for i in range(1,v+1):
        for j in range(len(X)):
            
            # Implement recursive function as described above
            if X[j] <= i:
                C[i] = C[i] or C[i-X[j]] # Add or so that all possible coin combinatons are checked 
            else:
                C[i] = False
            
    #Return last entry which gives us the final answer
    return C[v]

coins = [3,5,10]
change = 8

print(make_change(coins,change))