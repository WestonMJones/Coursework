import sys
def get_line(fname,parno,lineno):
    
    file = fname+".txt"
    p_count = 1
    line_count = 1
    
    on_space = False
    
    for line in open(file):
        
        
        
        if line=="\n":
            
            #Start of a paragraph
            if on_space == False:
                p_count=p_count+1
            on_space = True
            
        else:
        
            #Start of text / Still on text
            on_space = False
            if p_count == parno:
                               
                #On right paragraph
                if line_count == lineno:
                    
                    #On right line
                    t_return = line.rstrip()
                    return t_return
                else:
                    #Advance to next line
                    line_count=line_count+1

def parse_line(text):
    if "/" in text and text.count("/")>=3:
        locs = []
        for i in range(len(text)):
            if text[i]=="/":
                locs.append(i)
        num1 = text[locs[-3]+1:locs[-2]]
        num2 = text[locs[-2]+1:locs[-1]]
        num3 = text[locs[-1]+1:len(text)]
        text = text[0:locs[-3]:]
        if num1.isdigit() and num2.isdigit() and num3.isdigit():
            num1 = str(num1)
            num2 = int(num2)
            num3 = int(num3)
            return (num1,num2,num3,text)
    return None

keep_going=True

num1 = str(input("Please enter the file number ==> "))
num2 = int(input("Please enter the paragraph number ==> "))
num3 = int(input("Please enter the line number ==> "))

code = []
text=""

while keep_going==True:
    
    if text.count("END")==0:
        #Not at end
        
        #Check correctness of inputs
        temp = get_line(num1,num2,num3)
        if temp==None or parse_line(temp)==None:
            #Inputs are incorrect
            print("Incorrect starting point.")
            print("Error Code Below")
            print("____________________________________________________________")
            sys.exit()
        else:
            #Inputs correct -- advance
            num1,num2,num3,text=parse_line(get_line(num1,num2,num3))
        code.append(text)
    else:
        #At end
        keep_going=False     
code.pop()

f_out = open("program.py","w")
for l in code:
    out_string = l+"\n"
    f_out.write(out_string)
f_out.close()
print("")
import program
print("__________________________END OF EASTER EGG_____________________________")

#Test Cases
#1/5/4
#8/43/4
#3/87/7
