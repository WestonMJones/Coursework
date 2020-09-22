d1 = dict()
l1 = [ 5, 6, 7 ]
d1['car'] = l1
d1['bus'] = l1.copy()
l1.append( [8,9] )
d1['truck'] = d1['bus']
d1['bus'].append(10)
d1['truck'].pop(0)
print("list:", l1)
for v in sorted(d1.keys()):
    print("{}: {}".format( v, d1[v] ))