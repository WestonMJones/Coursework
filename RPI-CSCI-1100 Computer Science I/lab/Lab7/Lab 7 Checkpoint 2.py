#Things to test
#1,5,4 -- import webbrowser/2/3/3
#2,3,3 -- webbrowser.open("http://hackertyper.com/")/2/4/4
#2,4,4 -- END/0/0/0



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
            

name = str(input("Please enter the file number ==> "))
num1 = int(input("Please enter the paragraph number ==> "))
num2 = int(input("Please enter the line number ==> "))

print(get_line(name,num1,num2))