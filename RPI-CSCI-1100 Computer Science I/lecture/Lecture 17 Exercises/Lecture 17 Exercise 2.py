fname = input("Enter the name of the IMDB file ==> ")
print(fname)

movies = dict()
max_movie = ""
max_count = 0

for line in open(fname, encoding = "ISO-8859-1"):
    line.strip()
    a_line = line.split("|")
    name = a_line[0].strip()
    movie = a_line[1].strip()
    
    if not movie in movies:
        movies[movie]=set()
        movies[movie].add(name)
    else:
        movies[movie].add(name)
    if len(movies[movie])>max_count:
        max_count=len(movies[movie])
        max_movie = movie



print(max_count)
print(max_movie)

num_zero_count = 0

for i in movies.values():
    if len(i) == 1:
        num_zero_count=num_zero_count+1

print(num_zero_count)
    

    