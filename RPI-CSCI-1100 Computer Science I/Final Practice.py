def merge(L1,L2):
    i1 = 0
    i2 = 0
    L = []
    while i1 < len(L1) and i2 < len(L2):
        if L1[i1] < L2[i2]:
            L.append( L1[i1] )
            i1 += 1
        elif L1[i1]>L2[i2]:
            L.append( L2[i2] )
            i2 += 1
        else:
            L.append(L1[i1])
            L.append(L2[i2])
            i1+=1
            i2+=1
    L.extend(L1[i1:])  
    L.extend(L2[i2:])
    return L

def merge_sort(L): 
    workspace = [] 
    for i in range(len(L)): 
        workspace.append([L[i]])
    i = 0 
    while i < len(workspace) - 1: 
        L1 = workspace[i] 
        L2 = workspace[i + 1] 
        newL = merge(L1, L2) 
        workspace.append(newL) 
        i += 2
        
    if len(workspace) != 0: 
        L[:] = workspace[-1][:]


def ins_sort( v ):
    for i in range(1,len(v)):
        x = v[i]
        j = i-1
        while j >= 0 and v[j] > x:
            v[j+1] = v[j]
            j -= 1
        v[j+1] = x

def sel_sort( v ):
    for i in range(0, len(v)-1):
        k = i
        for j in range(i+1,len(v)):
            if v[j] < v[k]:
                k = j
        v[i],v[k] = v[k],v[i]

if __name__ == "__main__":
    v = [ 18.5, 9.4, 5.7, 18.8, 9.4,6.4 ]
    ins_sort(v)
    print(v)
    
    
    v = [ 18.5, 9.4, 5.7, 18.8, 9.4,6.4 ]
    sel_sort(v)
    print(v)
    
    
    v = [ 18.5, 9.4, 5.7, 18.8, 9.4,6.4 ]
    merge_sort(v)
    print(v)    


