def smallest_two(mylist):
    mylist.sort()
    newlist = []
    if len(mylist) > 0:
        newlist.append(mylist[0])
        if len(mylist) > 1:
            newlist.append(mylist[1])
    return newlist

values = [35, 34, 20, 40, 50, 30]
print(values)
print(smalles_two(values))
print(values)

#Prints out the sorted values