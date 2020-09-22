def recursive_max_impl( L, i ):
    '''
    The actual recursive function.
    '''
    if i == len(L)-1:
        return L[i]
    else:
        return max(L[i], recursive_max_impl(L,i+1) )

def recursive_max( L ):
    '''
    The driver for the recursive function.  This handles the special
    case of an empty list and otherwise makes the initial call to the
    recursive function.
    '''
    if len(L) == 0:
        return -99999    # By convention
    else:
        return recursive_max_impl( L, 0 )

if __name__ == "__main__":
    L1 = [ 5 ]
    print(recursive_max( L1 ))
    L2 = [ 24, 23.1, 12, 15, 1 ]
    print(recursive_max( L2))
    L2.append( 55 )
    print(recursive_max( L2 ))