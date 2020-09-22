# a program that uses a function to convert a celsius temperature
# to a temperature in fahrenheit

def convert2fahren(temp_c):
    return ((temp_c*1.8)+32)

print("0 ->",convert2fahren(0))
print("32 ->",convert2fahren(32))
print("100 ->",convert2fahren(100))

#0 -> 32.0
#32 -> 89.6
#100 -> 212.0