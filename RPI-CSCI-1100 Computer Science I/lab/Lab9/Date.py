'''
Start to the Date class for Lab 9.  This code will not run in Python
until three methods are added:
    __init__,
    __str__
    same_day_in_year
'''

days_in_month = [ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]
month_names = [ '', 'January', 'February', 'March', 'April', 'May', 'June', 'July',\
                    'August','September', 'October', 'November', 'December' ]

class Date(object):
    year=0
    month=0
    day=0
    
    def __init__(self,y=1900,m=1,d=1):
        self.year=int(y)
        self.month=int(m)
        self.day=int(d)
    
    def __str__(self):
        out_month = str(self.month).rjust(2,'0')
        out_day = str(self.day).rjust(2,'0')
        return str(self.year)+"/"+out_month+"/"+out_day
    
    def same_day_in_year(self, other):
        if self.month==other.month and self.day==other.day:
            return True
        else:
            return False
    
    def is_leap_year(self):
        if self.year%4==0 and not (self.year%100==0 and self.year%400!=0):
            return True
        else:
            return False
    
    def __lt__(self,other):
        if self.year==other.year:
            if self.month==other.month:
                if self.day==other.day:
                    return False
                else:
                    if self.day<other.day:
                        return True
                    else:
                        return False
            else:
                if self.month<other.month:
                    return True
                else:
                    return False
        else:
            if self.year<other.year:
                return True
            else:
                return False
            
    


if __name__ == "__main__":
    print("Testing code already in file")
    d1 = Date(1972, 3, 27)
    d2 = Date(1998, 4, 13)
    d3 = Date(1996, 4, 13)
    
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    
    print("d1.same_day_in_year(d2)", d1.same_day_in_year(d2))
    print("d2.same_day_in_year(d3)", d2.same_day_in_year(d3))
    
    print ()
    
    print("Added Testing Code for checkpoint 1")
    d1 = Date()
    d2 = Date()
    d3 = Date(1973,3,4)
    d4 = Date(1973,4,3)
    
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    print("d4: " + str(d4))
    
    print("d1.same_day_in_year(d2)", d1.same_day_in_year(d2))
    print("d2.same_day_in_year(d3)", d2.same_day_in_year(d3))
    print("d3.same_day_in_year(d4)", d3.same_day_in_year(d4))
    
    print("")
    
    print("Added testing Code for checkpoint 2 -- examples from pdf")
    
    d1 = Date(1972, 3, 27)
    d2 = Date(1998, 4, 13)
    d3 = Date(1998, 5, 13)
    d4 = Date(1998, 4, 11)
    
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    print("d4: " + str(d4))
    
    print("d1.is_leap_year", d1.is_leap_year())
    print("d2.is_leap_year", d2.is_leap_year())
    
    print("d1 < d2",d1<d2)
    print("d2 < d3",d2<d3)
    print("d3 < d4",d3<d4)
    
    print("")
    
    print("Added testing code for checkpoint 2 -- own examples -- testing leap years")
    d1 = Date(2000, 3, 27)
    d2 = Date(2004, 4, 13)
    d3 = Date(2008, 5, 13)
    d4 = Date(2012, 4, 11)
    d5 = Date(1900, 5, 13)
    d6 = Date(2002, 4, 11)
    d7 = Date(2011, 4, 11)
    
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    print("d4: " + str(d4))
    print("d5: " + str(d5))
    print("d6: " + str(d6))
    print("d7: " + str(d7))    
    
    print("d1.is_leap_year", d1.is_leap_year())
    print("d2.is_leap_year", d2.is_leap_year())
    print("d3.is_leap_year", d3.is_leap_year())
    print("d4.is_leap_year", d4.is_leap_year())
    print("d5.is_leap_year", d5.is_leap_year())
    print("d6.is_leap_year", d6.is_leap_year())
    print("d7.is_leap_year", d7.is_leap_year())
    
    print("")
    
    print("Adding testing code for checkpoint 2 -- own examples -- testing less than")
    d1 = Date(1999, 1, 1)
    d2 = Date(2000, 1, 1)
    d3 = Date(2001, 4, 1)
    d4 = Date(2001, 5, 1)
    d5 = Date(2002, 5, 11)
    d6 = Date(2002, 5, 13)
        
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    print("d4: " + str(d4))
    print("d5: " + str(d5))
    print("d6: " + str(d6))
    
    print("")
    
    print("d1 < d2",d1<d2)
    print("d2 < d1",d2<d1)
    print("d3 < d4",d3<d4)    
    print("d4 < d2",d4<d3)
    print("d5 < d6",d5<d6)
    print("d6 < d5",d6<d5)          