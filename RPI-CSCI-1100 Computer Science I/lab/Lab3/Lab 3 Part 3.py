#comment

def bpop_next(bpop):
    return max( int( ((10*bpop)/(1+0.1*bpop) - 0.05*bpop*fpop)) ,0 )

def fpop_next(fpop):
    return max( int((0.4 * fpop + 0.02 * fpop * bpop )) ,0 )

bpop = int(input("Number of bunnies ==> "))
print(bpop)
fpop = int(input("Number of foxes ==> "))
print(fpop)



print("Year 1:",bpop,fpop)

bpop_new = bpop_next(bpop)
fpop_new = fpop_next(fpop)
bpop = bpop_new
fpop = fpop_new

print("Year 2:",bpop,fpop)

bpop_new = bpop_next(bpop)
fpop_new = fpop_next(fpop)
bpop = bpop_new
fpop = fpop_new

print("Year 3:",bpop,fpop)

bpop_new = bpop_next(bpop)
fpop_new = fpop_next(fpop)
bpop = bpop_new
fpop = fpop_new

print("Year 4:",bpop,fpop)

bpop_new = bpop_next(bpop)
fpop_new = fpop_next(fpop)
bpop = bpop_new
fpop = fpop_new

print("Year 5:",bpop,fpop)

bpop_new = bpop_next(bpop)
fpop_new = fpop_next(fpop)
bpop = bpop_new
fpop = fpop_new




