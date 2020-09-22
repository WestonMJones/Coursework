all: mult

# Change this to whatever compiler you use for OpenMP
CC = gcc
# You can put more options, such as -O1, at the end of the CFLAGS assignment
CFLAGS = -Wall -fopenmp -std=c99

mult: matrixMult.c
	$(CC) $(CFLAGS) matrixMult.c -o mult
