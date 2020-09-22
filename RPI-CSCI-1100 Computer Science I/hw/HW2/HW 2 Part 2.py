"""
This program performs the Einstein Parlor Trick 
It asks the user to provide a 5 digit number where the first and third 
digits difer by at least 2 then performs a series of reversals to produce 
the number 1089 regardless of what the user entered.
"""

#functions
def reverse3(num):
    first_char = str(num//100)
    second_char = str((num%100)//10)
    third_char = str(num%10)
    
    return int(third_char+second_char+first_char)

def reverse5(num):
    first_char = str(num//10000)
    second_char = str((num//1000)%10)
    third_char = str( (num%1000)//100 )
    fourth_char = str((num//10)%10)
    fifth_char = str(num%10)
    return int(fifth_char+fourth_char+third_char+second_char+first_char)

#main body
print("Enter a 5 digit number whose first and third digits must differ by at least 2.")
print("The answer will be 1089, if your number is valid")
num = int(input("Enter a value ==> "))
print(num)
print("")
print("Here is the computation:")
print(num,"reversed is",reverse5(num))

max_num = max((num//100),int((reverse5(num))%1000))
min_num = min((num//100),int((reverse5(num))%1000))
new_num = max_num-min_num


print(max_num,"-",min_num,"=",new_num)
print(new_num,"+",reverse3(new_num),"=",new_num+reverse3(new_num))
print("You see, I told you.")
