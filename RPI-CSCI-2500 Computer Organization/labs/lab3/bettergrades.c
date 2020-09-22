#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct student
{
	char name[100]; // No one should have a name longer than this
	int *grades; // This is the pointer to hold the (integer) grades
	int count; // The number of grades
};


int main() {


	int num_stu, num_grades;
	char temp_name[100];
	float total;

	printf("How many students are there? \n");
	scanf("%d",&num_stu);

	struct student *students = calloc(num_stu,sizeof(struct student));
	float * averages = calloc(num_stu,sizeof(float));

	for (int i=0;i<num_stu;i++) {
		printf("Enter the name of student %d: \n",i );
		scanf("%s",temp_name);
		strcpy(students[i].name,temp_name);
		printf("How many grades does %s have? ",students[i].name);
		scanf("%d",&num_grades);
		students[i].grades = calloc(num_grades,sizeof(int));

		total = 0;

		for (int x=0;x<num_grades;x++) {
			printf("Enter the next grade: ");
			scanf("%d",&students[i].grades[x]);
			total = total + (float)students[i].grades[x];
		}

		averages[i] = total / num_grades;
	}

	
	for (int y=0;y<num_stu;y++) {
		printf("%s has an average grade of %.2f\n",students[y].name,averages[y] );
	}



	return 0;
}