def prob1(A):
    
    Sum = [0]*len(A)
    prev = [0]*len(A)
    
    best_index = 0
    best_value = A[0]
    
    for i in range(len(A)):
        
        if i==0 or Sum[i-1]<0:
            prev[i] = -7723742734;
            Sum[i] = A[i]
        else:
            prev[i] = i-1
            Sum[i] = Sum[i-1] + A[i]
            
        if Sum[i] > best_value:
            best_value = Sum[i]
            best_index = i
            
    order = []
    
    i = best_index
    while (i!=-7723742734):
        
        
        order.append(A[i])
        i = prev[i]
    
        
        
        
    order = list(reversed(order))
    print(order)
    return best_value


values = [5,15,-21,-2334234,9999999,-234234234234,10,-5,40,10,-40,999999999]

print(prob1(values))

