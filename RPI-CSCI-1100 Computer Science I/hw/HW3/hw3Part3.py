"""
THis program creates a virtual space with an entity in the middle
that can be commanded up to five times by the user.
"""

#functions
def move(x,y,direction,amount):
    if direction=="up":
        y-=amount
    elif direction=="down":
        y+=amount
    elif direction=="left":
        x-=amount
    elif direction=="right":
        x+=amount
    if x<0:
        x=0
    if x>400:
        x=400
    if y<0:
        y=0
    if y>400:
        y=400
    return (x,y)

def turn(direction):
    if direction=="up":
        return "left"
    elif direction=="left":
        return "down"
    elif direction=="down":
        return "right"
    elif direction=="right":
        return "up"

#Variables
pos = (200,200)
direction = "right"
awake = True
cmds = []

#main body
for i in range(5):
    print("Turtle:",pos,"facing:",direction)
    if awake:
        cmd = input("Command (move,jump,turn,sleep) => ")
        print(cmd)
        cmds.append(cmd)
        if cmd.lower()=="move":
            #Move command
            pos = move(pos[0],pos[1],direction,20)
        elif cmd.lower()=="jump":
            #Jump command
            pos = move(pos[0],pos[1],direction,50)
        elif cmd.lower()=="turn":
            #Turn command
            direction=turn(direction)
        elif cmd.lower()=="sleep":
            #Sleep command
            print("Turtle falls asleep.")
            awake=False
    else:
        #Turtle is asleep
        print("Turtle is currently sleeping ... no command this turn.")
        awake=True

print("Turtle:",pos,"facing:",direction)
print("")
print("All commands entered:",cmds)
cmds.sort()
print("Sorted commands:",cmds)
