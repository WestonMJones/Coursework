import time
from urllib import request
def decode(word):
    s = 2
    d = ''
    for l in word:
        d += chr(ord(l)+s)
        s *= -1
    return d
for line in request.urlopen(decode('fvrr81-yuy,eq0prg0cfs1|ugdcn-eqeg3/2.1dcjn02/6-gei-3,vvv')):
    for word in line.split():
        print("{:s} ".format(word.decode("utf-8")), end="")
        time.sleep(0.1)
    print()
    time.sleep(1)


