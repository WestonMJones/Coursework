#include "lib/unp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int global_child_count;

void sig_child(int signo) {
	pid_t pid;
	int stat;

	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		global_child_count++;
		printf("Parent sees child PID %d has been terminiated\n",pid );
	}
	return;
}

/*int main() {
	

	
	int n = fork();


	if (n==0) {
		return 0;
	} else {
		sleep(2);
	}
	
	return 0;
}*/

int main() {

	Signal(SIGCHLD, sig_child);

	int num_children = 0;
	int pid;

	printf("Number of children to spawn: ");
	scanf("%d", &num_children);

	srand(time(0)); 
	int r[num_children];
	for (int i=0;i<num_children;i++) {
		r[i] = (rand() % 4)+1;
	}




	for (int i=0;i<num_children;i++) {
		pid = fork();
		if (pid > 0){
	        /* Parent process */
	        printf("Parent spawned child PID %d\n", pid);
	        
	    } else{
	        /* Child process */
	    	printf("Child PID %d dying in %d seconds.\n",getpid(), r[i] );
	    	sleep(r[i]);
	    	printf("Child PID %d terminating\n",getpid() );
	    	break;
	    }
	}

	if (pid > 0) {
		while(1) {
			if (global_child_count==num_children) {
				break;
			}
		}
	}
	

	return 0;
}
