#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

long r;
long i;


int main() {



	printf("Gimme a positive integer: ");
	scanf("%li",&r);



	for (i=r-1;i>0;i--) {
		r = r * i;
	}

	printf("%li",r);
 
	return 0;
}