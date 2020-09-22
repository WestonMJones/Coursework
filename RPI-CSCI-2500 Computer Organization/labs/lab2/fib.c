#include <stdio.h>
#include <stdlib.h>


int fib(int n) {
	int a, b, t, x;
	a = 1;
	b = 1;
	for (x=0;x<n-2;x++) {
		t = b;
		b = a+b;
		a = t;
	}
	return b;
}


int main(int argc,char **argv) {
	int n;
  	n = atoi(argv[1]);
  	printf("The fibonacci number at position %d is: %d (slow way)",n,fib(n));
	return 0;
}