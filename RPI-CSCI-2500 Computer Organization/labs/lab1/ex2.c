#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int n;
int i;
int ii;
int count;

void make_triangle(int length) {
	for (i=1;i<length+1;i++) {
		for (ii=0;ii<i;ii++) {
			printf("*");
		}
		printf("\n");
	}
	float hyp = sqrt(((length*length)*2));
	printf("The hypothenuse is %.2f \n",hyp);
}


int main() {
	
	printf("Printing 5 triangles\n");
	for (count=0;count<5;count++) {

		printf("What is n? ");
		scanf("%d",&n);

		make_triangle(n);

	}

	return 0;
}



