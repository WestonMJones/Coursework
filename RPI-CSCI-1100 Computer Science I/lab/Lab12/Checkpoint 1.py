def add(m,n):
    if n == 0:
        return m
    else:
        return add(m,n-1) + 1
    return

def mult(m,n):
    if n-1==0:
        return m
    else:
        return add(mult(m,n-1),m)

def power(x,n):
    if n-1==0:
        return x
    else:
        return mult(x,power(x,n-1))


print(add(5,3))
print(mult(8,3))
print(power(6,4))