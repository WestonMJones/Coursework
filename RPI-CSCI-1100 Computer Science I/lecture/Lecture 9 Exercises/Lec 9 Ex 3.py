dumb_list = []
stop = False
while stop==False:
    temp_var = int(input("Enter a value (0 to end): "))
    print(temp_var)
    if temp_var!=0:
        #Stuff
        dumb_list.append(temp_var)
    else:
        stop=True
min_val = min(dumb_list)
max_val = max(dumb_list)
avg = round(sum(dumb_list)/len(dumb_list),1)
print("Min:",min_val)
print("Max:",max_val)
print("Avg:",avg)

