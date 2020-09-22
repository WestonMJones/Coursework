def head_and_tail(L):
    from_back = L.pop()
    from_front = L.pop(0)
    L.append(from_front)
    L.insert(0,from_back)

L1 = [ [1, 2], 3 ]
L3 = L1.copy()
L2 = L1
L2[-1] = 5
L2.insert(1,6)
head_and_tail(L1)

print(L1[0], L1[-1], len(L1))
print(L2[0], L2[-1], len(L2))
print(L3[0], L3[-1], len(L3))