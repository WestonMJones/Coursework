def explore2(g,v,visit):
    print(v,end=" ")
    visit[v] = True
    for con_vert in g[v]:
        if visit[con_vert] == False:
            explore2(g,con_vert,visit)

def explore(g,v,visit,pre,post,c):

    visit[v] = True
    pre[v] = c[0]
    
    #print("\nCurrently on Node",v,"with preorder",c[0])    

    for con_vert in g[v]:
        if visit[con_vert] == False:
            c[0]+=1
            explore(g,con_vert,visit,pre,post,c)
        else:
            #print("Node",con_vert,"has already been visited")
            True
    
    #print("\nBack to Node",v,"with postorder",c[0])
    post[v] = c[0]
    return

fname = "test2.txt"

alist = dict()

for line in open(fname):
    data = line.split(" ")
    start = int(data[0])
    end = int(data[1])
    
    if start not in alist:
        alist[start] = list()
    if end not in alist:
        alist[end] = list()
        
    alist[start].append(end)

size = len(alist)
visited = dict()
preorder = dict()
count = [0]
postorder = dict()

for i in range(1,size+1):
    visited[i]=False
    preorder[i]=0
    postorder[i]=0

#Step 1 -- Create reverse graph
ralist = dict()

for key in alist:
    
    if key not in ralist:
        ralist[key] = list()
    
    for val in alist[key]:
        if val not in ralist:
            ralist[val] = list()
        
        ralist[val].append(key)
    
#Step 2 -- Run DFS on reverse graph
for vertex in range(1,size+1):
    if visited[vertex]==False:
        explore(ralist,vertex,visited,preorder,postorder,count)

    
#Step 3 -- Select highest postorders
for i in range(1,size+1):
    visited[i]=False
    
max_post = 0
max_post_vert = 0
all_visited=False

while all_visited==False:
#for x in range(100):
    all_visited=True
    for i in range(1,size+1):
        if visited[i]==False:
            all_visited=False
            
    
    if all_visited==False:
        max_post = 0
        max_post_vert = 1
        
        for v in range(1,size+1):
            if visited[v]==False:
                if postorder[v]>max_post:
                    max_post = postorder[v]
                    max_post_vert = v
        if (max_post_vert!=0):
            explore2(alist,max_post_vert,visited)
            print("")
                       
        