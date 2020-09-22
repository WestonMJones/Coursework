"""
 -the word has at least 8 characters,
 -starts with a vowel,
 -has alternating vowels and consonants, and
 -the consonants are in increasing alphabetical order.
"""

#functions
def is_alternating(word):
    
    #set variables for the function
    vowels = "aeiou"
    last_consonant = ""
    on_vowel = True
        
    #First condition
    if len(word)<8:
        return False
    
    #Second condition
    if not word[0] in vowels:
        return False
    
    #Third and Fourth Conditions
    for i in range(len(word)):
        #Check each character
        # i goes from actual length-1 to 1
        # 123456789 --> 1,2,3,4,5,6,7,8
        
        if on_vowel==False:
            if word[i] in vowels:
                #Check for two vowels
                return False
            if last_consonant>word[i].lower() or last_consonant==word[i].lower():
                #Check to see if the constants are increasing
                return False
            on_vowel=True
            
            last_consonant = word[i].lower()
            
        else:
            on_vowel=False
        
    return True

#main body
word = str(input("Enter a word => "))
print(word)

if is_alternating(word)==True:
    print("The word '",word,"' is alternating",sep="")
else:
    print("The word '",word,"' is not alternating",sep="")