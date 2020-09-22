"""
This program allows the user to encrypt normal text
and decryupt cipher text using a simple substitution algorithm.
The program also outputs the difference in length between the user input
and program output
"""

#FUnctions Here
def encrypt(word):
    
    word = word.replace(" a","%4%")
    word = word.replace("he","7!")
    word = word.replace("e","9(*9(")
    word = word.replace("y","*%$")
    word = word.replace("u","@@@")
    word = word.replace("an","-?")
    word = word.replace("th","!@+3")
    word = word.replace("o","7654")
    word = word.replace("9","2")    
    
    return word

def decrypt(word):
    word = word.replace("2","9")  
    word = word.replace("7654","o")
    word = word.replace("!@+3","th")
    word = word.replace("-?","an")
    word = word.replace("@@@","u")
    word = word.replace("*%$","y")
    word = word.replace("9(*9(","e")
    word = word.replace("7!","he")
    word = word.replace("%4%"," a")
    
    return word

#Main Body Here
input_string = input("Enter 'E' for encrypt or 'D' for decrypt ==> ")
print(input_string)

if input_string.lower()=="e":
    #Encrypt
    text = input("Enter regular text ==> ")
    print(text)
    print("")      
    
    print("Encrypted as ==>",encrypt(text))
    print("Difference in length ==>",abs(len(text)-len(encrypt(text))))
elif input_string.lower()=="d":
    #Decrypt
    text = input("Enter cipher text ==> ")
    print(text)
    print("")    
    
    print("Deciphered as ==>",decrypt(text))
    print("Difference in length ==>",abs(len(text)-len(decrypt(text))))      
    
else:
    #Invalid Character
    print("I didn't understand ... exiting")
    