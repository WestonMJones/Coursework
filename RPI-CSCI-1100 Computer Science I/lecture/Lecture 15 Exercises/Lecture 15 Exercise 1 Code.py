s1 = set([0,1,2])
s2 = set(range(1,9,2))
print('A:', s1.union(s2))

print('B:', s1)

s1.add('1')
s1.add(0)
s1.add('3')
s3 = s1 | s2
print('C:', s3)

print('D:', s3 - s1)