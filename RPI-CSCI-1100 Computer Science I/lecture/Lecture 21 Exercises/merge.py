def merge(L1,L2):
    '''
    Merge the contents of two lists, each of which is already sorted
    into a single sorted list.
    '''
    i1 = 0
    i2 = 0
    L = []
    '''
    Repeated choose the smallest remaining item from the lists until one
    list has no more items that have not been merged.
    '''
    while i1 < len(L1) and i2 < len(L2):
        if L1[i1] < L2[i2]:
            L.append( L1[i1] )
            i1 += 1
        elif L1[i1]>L2[i2]:
            L.append( L2[i2] )
            i2 += 1
        else:
            L.append(L2[i2])
            i1+=1
            i2+=1
    L.extend(L1[i1:])   #  copy remaining items from L1, if any
    L.extend(L2[i2:])   #  copy remaining items from L2, if any
    return L

    #L1 [1, 2, 3, 4], L2 [1, 2, 3, 4], Merged [1, 2, 3, 4]
    #L1 [1, 2, 3, 4], L2 [5, 6], Merged [1, 2, 3, 4, 5, 6]
    #L1 [44, 55, 66, 77], L2 [1, 10, 44, 55], Merged [1, 10, 44, 55, 66, 77]

if __name__ == "__main__":
    L1 = [ 1,2,3,4 ]
    L2 = [ 1,2,3,4 ]
    print("L1 {}, L2 {}, Merged {}".format(L1,L2,merge(L1,L2)))

    L1 = [ 1,2,3,4 ]
    L2 = [ 5,6 ]
    print("L1 {}, L2 {}, Merged {}".format(L1,L2,merge(L1,L2)))    

    L1 = [44, 55, 66, 77]
    L2 = [1, 10, 44, 55]
    print("L1 {}, L2 {}, Merged {}".format(L1,L2,merge(L1,L2)))
    