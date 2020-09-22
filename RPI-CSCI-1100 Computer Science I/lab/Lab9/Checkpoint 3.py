from Date import *
month_names = ['January', 'February', 'March', 'April', 'May', 'June', 'July',\
                    'August','September', 'October', 'November', 'December' ]
birthdays = []

for line in open('birthdays.txt'):
    data = line.split()
    data[1].lstrip("0")
    data[2].lstrip("0")
    
    d = Date(data[0],data[1],data[2])
    
    birthdays.append(d)

earliest = Date(3000,3000,3000)
latest = Date(1,1,1)
month_count = [0]*12

for b in birthdays:
    print(str(b))
    if b<earliest:
        earliest = b
    if not b<latest:
        latest = b
    month_count[b.month-1]+=1

max_index=month_count.index(max(month_count))

print("")
print("The earliest birthday is",str(earliest))
print("The latest birthday is",str(latest))
print("The most common month is",month_names[max_index])