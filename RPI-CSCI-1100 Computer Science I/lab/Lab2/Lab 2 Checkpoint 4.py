fname = input("Please enter your first name: ")
lname = input("Please enter your last name: ")
lname = lname + "!"
maxnum = max(int(len(fname)+6),int(len(lname)+6),int(len("** Hello,")+3))
print("*" * maxnum)
print("** Hello,",(" "*((maxnum-3)-len("** Hello,")))," **",sep='')

print("** ",fname," "*((maxnum-6)-len(fname))," **",sep="")
print("** ",lname," "*((maxnum-6)-len(lname))," **",sep="")


#print("** ",fname,(" "*((maxnum-3)-len(fname))," **",sep='')
#print("** ",lname,(" "*((maxnum-3)-len(lname))," **",sep='')
print("*" * maxnum)