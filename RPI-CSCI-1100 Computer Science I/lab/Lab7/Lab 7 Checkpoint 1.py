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
        
    

print(parse_line("Test/12/3/4"))
print(parse_line("Here is some random text, like 5/4=3./12/3/4"))
print(parse_line("Here is some random text, like 5/4=3./12/3/4as"))
print(parse_line("Here is some random text, like 5/4=3./12/412/a/3/4"))
print(parse_line(" Here is some spaces 12/32/4"))
print(parse_line(" Again some spaces\n/12/12/12"))
