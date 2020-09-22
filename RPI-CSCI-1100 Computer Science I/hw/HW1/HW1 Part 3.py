#This program asks a user for parts of speech to fill out a madlib
#which is then outputed using the user input

#user input
print("Let's play MadLibs for Homework 1")
print("Type one word responses to the following:")
name = input("proper_name ==> ")
print(name)
adj1 = input("adjective ==> ")
print(adj1)
n1 = input("noun ==> ")
print(n1)
v1 = input("verb ==> ")
print(v1)
n2 = input("noun ==> ")
print(n2)
emo1 = input("emotion ==> ")
print(emo1)
v2 = input("verb ==> ")
print(v2)
n3 = input("noun ==> ")
print(n3)
n4 = input("noun ==> ")
print(n4)
season = input("season ==> ")
print(season)
emo2 = input("emotion ==> ")
print(emo2)
team_name = input("team-name ==> ")
print(team_name)
adj2 = input("adjective ==> ")
print(adj2)
print("")
print("Here is your Mad Lib...")
print("")

#Outputting the actual MadLib
print("Hello ",name,",",sep="")
print("  Good morning!  Are you looking forward to a/an ",adj1," ",n1,"?",sep="")
print("  You will",v1,"a lot of",n2,"and feel",emo1,"when you do.")
print("  If you do not, you will ",v2," this ",n3,".",sep="")
print("")
print("  Did you watch the ",n4," this ",season,"?",sep="")
print("  Were you",emo2,"when the",team_name,"won?")
print("  Have a/an",adj2,"day!")


#Hello <proper name>,
#Good morning! Are you looking forward to a/an <adjective> <noun>?
#You will <verb> a lot of <noun> and feel <emotion> when you do.
#If you do not, you will <verb> this <noun>.
#Did you watch the <noun> this <season>?
#Were you <emotion> when the <team-name> won?
#Have a/an <adjective> day!

