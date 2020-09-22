# Step 1 -- Alice generates p, g, and b. Compute  B. Send p, g, and B to Bob
p = 17
g = 29
b = 45
B = (g^b) % p 


# Step 2 -- Bob generates number a and computes A. Sends A to Alice
a = 76
A = (g^a) % p
K1 = (B^a) % p


# Step 3 -- Alice
K2 = (A^b) % p

print(K1)
print(K2)




