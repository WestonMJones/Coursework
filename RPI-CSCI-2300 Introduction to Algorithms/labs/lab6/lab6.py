from heapdict import heapdict
import math

fname = "example.txt"
startNode = 1 

graph = dict()

for line in open(fname):
    data = line.split(" ")
    start = int(data[0])
    end = int(data[1])
    
    if start not in graph:
        graph[start] = list()
    if end not in graph:
        graph[end] = list()
        
    graph[start].append(end)

numV = len(graph)+1
dist = [math.inf]*numV
prev = [0]*numV

l = [[0 for x in range(numV)] for y in range(numV)]

for line in open(fname):
    data = line.split(" ")
    start = int(data[0])
    end = int(data[1])
    weight = int(data[2])
    
    l[start][end] = weight

#for u in range(1,numV):
    #for v in graph[u]:
        #print(u,"to",v,"is",l[u][v])
        

#Actual Dijkstra implementation
dist[startNode] = 0
H = heapdict()

for i in range(1,numV):
    H[i] = dist[i]
    
while len(H)!=0:
    u = H.popitem()[0]
    
    for v in graph[u]:
        if dist[v] > dist[u] + l[u][v]:
            dist[v] = dist[u] + l[u][v]
            prev[v] = u
            #decreasekey(H, v)
            H[v]=dist[v]-1


for u in range(1,numV):
    print(u,": ",dist[u],", [ ",startNode,sep="",end="")
    
    i = prev[u]
    while prev[i]!=0:
        print(",",i,sep="",end="")
        i=prev[i]
    
    if u != startNode:
        print(",",u,sep="",end="")
    print(" ]")