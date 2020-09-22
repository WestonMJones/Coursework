#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main() {

	int num_grades=0;
	printf("How many grades does the student have? ");
	scanf("%d",&num_grades);

	assert(num_grades!=0);

	int * grades = calloc(num_grades,sizeof(int));
	float total=0;

	for (int i=0;i<num_grades;i++) {
		printf("Enter the next grade: ");
		scanf("%d",&grades[i]);
		total = total + (float)grades[i];
	}

	float avg = total/(float)num_grades;

	printf("The average grade is %.2f \n", (avg));



	return 0;
}