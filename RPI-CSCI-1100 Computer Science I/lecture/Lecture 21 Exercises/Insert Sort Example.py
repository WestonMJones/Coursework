def ins_sort(v):
    for i in range(1, len(v)):
        j=i-1
        x=v[i]
        while i>= 0 and x < v[i]:
            v[j+1]=v[i]
            i-=1
        v[j+1]=x
