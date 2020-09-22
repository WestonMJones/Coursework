# Version 1
sum = 0
for i in range(10):
    for j in range(10):
        sum += 1
print(sum)

# Version 2
sum = 0
for i in range(10):
    for j in range(i+1,10):
        sum += 1
print(sum)

# Version 3
sum = 0
for i in range(10):
    sum += 1
for j in range(10):
    sum += 1
print(sum)