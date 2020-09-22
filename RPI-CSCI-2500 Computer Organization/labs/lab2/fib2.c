#include <stdio.h>
#include <stdlib.h>

int * numbers;

int fib(int n) {
	int i;
	if (numbers[n]==0) {
		// calculate up to that point

		for (i=2;i<n+1;i++) {
			numbers[i]=numbers[i-2]+numbers[i-1];
		}
	}

	
	return numbers[n];
}


int main(int argc,char **argv) {
	int n,i;
  	n = atoi(argv[1]);

  	numbers = (int*)calloc(n,sizeof(int));
  	for (i=0;i<n;i++) {
  		numbers[i] = 0;  
  	}
  	numbers[0]=1;
  	numbers[1]=1;




  	printf("The fibonacci number at position %d is: %d (fast way)",n,fib(n-1));
	return 0;
}