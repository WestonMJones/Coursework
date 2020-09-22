census = [ 340, 589, 959, 1372, 1918, 2428, 3097, 3880, 4382, 5082, \
            5997, 7268, 9113, 10385, 12588, 13479, 14830, 16782, \
            8236, 17558, 17990, 18976, 19378 ]
avg = 0
i=1
while i< len(census):
    avg+= ((census[i]-census[i-1])/census[i-1])*100
    i += 1

avg = avg / (len(census)-1)
print("Average = ",round(avg,1),"%",sep="")
