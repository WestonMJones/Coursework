#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_CHILD 5

struct Pairs {
	int first;
	int second;
};


void* add(void * pair_point) {
	struct Pairs * pair = (struct Pairs*)pair_point;
	int n1 = pair->first;
	int n2 = pair->second;

	//b ? return 1 + add(a,b-1) : return a;
	if (n2!=0) {
		struct Pairs temp;
		temp.first = n1;
		temp.second = n2-1;

		int temp2 = (1 + add(&temp));

		return (void*)temp2;
	} else {
		return (void*)n1;
	}
}

int main(){

	//printf("Starting!\n");
	pthread_t children[NUM_CHILD*(NUM_CHILD-1)];
	int count = 0;
	for (int x=1;x<NUM_CHILD;x++) {
		for (int y=1;y<NUM_CHILD+1;y++) {

			pthread_t tid;

			struct Pairs *temp = malloc(sizeof(struct Pairs));
			temp->first = x;
			temp->second = y;

			int val = pthread_create(&tid, NULL, add, (void*)temp );
			if (val<0){
				return -1;
			} else{
				//printf("X is %d, Y is %d, count is %d\n",x,y,count);
				children[count] = tid;
				count++;
			}			
		}
	}

	//printf("At second part!\n");
	count = 0;
	for (int x=1;x<NUM_CHILD;x++) {
		for (int y=1;y<NUM_CHILD+1;y++) {

			//printf("X is %d, Y is %d, count is %d\n",x,y,count);

			int *ret_value;
			pthread_join(children[count],(void**)&ret_value);
			//printf("Does it get this far?\n");
			count++;
			printf("[%d + %d] Child %d is %d\n",x,y,count,(int)ret_value);
		}
	}

	return 0;
}