def ok_to_add(row, column, number):
    number = str(number)
    
    #Loop through every part of the board. x = row, y = column
    for x in range(len(bd)): 
        for y in range(len(bd[x])):
            
            #If the column contains the same number, return false
            if(bd[row][y] == number):
                return False
            
            #If row contains same number,return false
            elif(bd[x][column] == number):
                return False
            
            #Check each 3 by 3 grid
            
            #Checks top third of board
            if(row in [0, 1, 2] and x in [0, 1, 2]):
                
                #Checks top left 3x3
                if(column in [0, 1, 2] and y in [0, 1, 2]):
                    if(number == bd[x][y]):
                        return False 
                
                #Checks top middle 3x3
                elif(column in [3, 4, 5] and y in [3, 4, 5]):
                    if(number == bd[x][y]):
                        return False
                
                #Checks top right 3x3
                elif(column in [6, 7, 8] and y in [6, 7, 8]):
                    if(number == bd[x][y]):
                        return False
            
            #Checks center third of board
            elif(row in [3, 4, 5] and x in [3, 4, 5]):
                
                #Checks center left 3x3
                if(column in [0, 1, 2] and y in [0, 1, 2]):
                    if(number == bd[x][y]):
                        return False
                
                #Checks center middle 3x3
                elif(column in [3, 4, 5] and y in [3, 4, 5]):
                    if(number == bd[x][y]):
                        return False
                    
                #Checks center right 3x3
                elif(column in [6, 7, 8] and y in [6, 7, 8]):
                    if(number == bd[x][y]):
                        return False
            
            #Checks bottom third
            elif(row in [6, 7, 8] and x in [6, 7, 8]):
                
                #Checks bottom left 3x3
                if(column in [0, 1, 2] and y in [0, 1, 2]):
                    if(number == bd[x][y]):
                        return False
                    
                #Checks bottom middle 3x3
                elif(column in [3, 4, 5] and y in [3, 4, 5]):
                    if(number == bd[x][y]):
                        return False
                
                #Checks bottom right 3x3
                elif(column in [6, 7, 8] and y in [6, 7, 8]):
                    if(number == bd[x][y]):
                        return False
    return True


bd = [ [ '1', '.', '.', '.', '2', '.', '.', '3', '7'],
       [ '.', '6', '.', '.', '.', '5', '1', '4', '.'],
       [ '.', '5', '.', '.', '.', '.', '.', '2', '9'],
       [ '.', '.', '.', '9', '.', '.', '4', '.', '.'],
       [ '.', '.', '4', '1', '.', '3', '7', '.', '.'],
       [ '.', '.', '1', '.', '.', '4', '.', '.', '.'],
       [ '4', '3', '.', '.', '.', '.', '.', '1', '.'],
       [ '.', '1', '7', '5', '.', '.', '.', '8', '.'],
       [ '2', '8', '.', '.', '4', '.', '.', '.', '6'] ]

#Loop through the rows
for x in range(len(bd)): 
    #If row is a border, print border before numbers
    if(x == 0 or x == 3 or x == 6):
        print('-' * 25) 
    
    #Loop through the columns for this row 
    for y in range(len(bd[x])): 
        
        #If column is after a border, print border before number
        if( y == 0 or y == 3 or y == 6):
            print('|', end=' ')
        
        #Print number in that column
        print(bd[x][y], end=' ')
        
        #If column is before a border, print before after number
        if (y == 8):
            print('|')
    
    #If row is before the end, print border after the numbers
    if(x == 8):
        print('-' * 25)

x1 = int(input('Enter a row from 0 to 8 ==> '))
y1 = int(input('Enter a column from 0 to 8 => '))
numb = int(input('Enter the number from 1 to 9 => '))

print(ok_to_add(x1, y1, numb))
