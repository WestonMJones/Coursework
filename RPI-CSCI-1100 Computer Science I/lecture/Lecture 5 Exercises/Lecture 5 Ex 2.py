# This program uses a function to convert user input strings and print them 
# with "*" frames around them.

def frame_string(var1):
    print("*" * int(len(var1)+6))
    print("**",var1,"**")
    print("*" * int(len(var1)+6))    

frame_string("Spanish Inquisition")
print("")
frame_string("Ni")