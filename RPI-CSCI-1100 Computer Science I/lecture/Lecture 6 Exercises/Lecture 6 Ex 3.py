# This program calculates the average of two numbers where
# one is greater than 10 and the other is less than 10


n1 = float(input("Enter the first number: "))
print(n1)
n2 = float(input("Enter the second number: "))
print(n2)

if n1 > 10 and n2 > 10:
    print("Both are above 10.")
elif n1 <= 10 and n2 <= 10:
    print("Both are below 10.")

print("Average is",round(((n1+n2)/2),2))