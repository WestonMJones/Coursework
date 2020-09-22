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
        
