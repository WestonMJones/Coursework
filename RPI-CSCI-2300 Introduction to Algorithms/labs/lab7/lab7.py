X = "CATAAGCTTCTGACTCTTACCTCCCTCTCTCCTACTCCTGCTCGCATCTGCTATAGTGGAGGCCGGAGCAGGAACAGGTTGAACAG"
Y = "CGTAGCTTTTTGGTTAATTCCTCCTTCAGGTTTGATGTTGGTAGCAAGCTATTTTGTTGAGGGTGCTGCTCAGGCTGGATGGA"
       
#X = "EXPONENTIAL"
#Y = "POLYNOMIAL"


def diff(i,j):
       if (X[i])==(Y[j]):
              return 0
       else:
              return 1

#Main code
if __name__=='__main__':
          
       X = " "+X
       Y = " "+Y
       m = len(X)
       n = len(Y)
       
       E = [[1000 for x in range(n+1)] for y in range(m+1)]
       

       for i in range(m):
              E[i][0] = i
       for j in range(1,n):
              E[0][j] = j
       for i in range(1,m):
              for j in range(1,n):
                     choices = []
                     choices.append(E[i-1][j]+1) #down
                     choices.append(E[i][j-1]+1) #right
                     choices.append(E[i-1][j-1]+diff(i,j)) #diag
                     
                     E[i][j] = min(choices)
       
       print("")
       print("    ",end="")
       for i in range(n):
              print(Y[i].ljust(4),end="")
       print("")
       for i in range(m):
              print(X[i].ljust(4),end="")
              
              for j in range(n):
                     value = str(E[i][j]).ljust(4)
                     print(value,end="")
              print("")
                      
       
       
       print("")
       print("Edit Distance =", E[m-1][n-1])
       print("Alignment:")
       
       

       i=m-1
       j=n-1
       alignment = []
       
       while (i!=0 and j!=0):
              choices = []
              choices.append(E[i-1][j]) #down              
              choices.append(E[i-1][j-1]) #diag              
              choices.append(E[i][j-1]) #right
              
              choice = choices.index(min(choices))
              
                           
              if choice==0:
                     #print("up")
                     alignment.append("down")
                     i=i-1
                    
                     
                    
              elif choice==2:
                     #print("left")
                     alignment.append("right")
                     j=j-1
                                       
                     
                     
              elif choice==1:
                     #print("diag")
                     alignment.append("diag")
                     i=i-1
                     j=j-1
                   
              else:
                     print("WTF")
                     break             
              
              
              
x_print = ""
y_print = ""
xc = 1
yc = 1

alignment = alignment[:-1]
alignment = list(reversed(alignment))

for direction in alignment:
       if direction == "diag":
              x_print+=X[xc]
              y_print+=Y[yc]
              xc+=1
              yc+=1
       elif direction == "down":
              x_print+=X[xc]
              y_print+="-"
              xc+=1
       elif direction == "right":
              y_print+=X[yc]
              x_print+="-"
              yc+=1
              

#print(alignment)
print(x_print+X[m-1])
print(y_print+Y[n-1])
       
                                          
      
       
              
       
       
       
    
