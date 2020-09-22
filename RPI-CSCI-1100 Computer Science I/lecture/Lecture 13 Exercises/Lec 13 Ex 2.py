read_file = input("Enter the scores file: ")
read_file = read_file.strip()
print(read_file)
write_file = input("Enter the output file: ")
print(write_file)

f = open(read_file)

out_list = []
for i in open(read_file):
    i = int(i.replace("\n",""))
    out_list.append(i)

out_list.sort()

w = open(write_file,"a")


for i in range(len(out_list)):
    num = str(i)
    line = num+":   "+str(out_list[i])+"\n"
    w.write(line)
w.close()