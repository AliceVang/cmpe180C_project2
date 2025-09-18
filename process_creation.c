#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;

	// fork a child process
	pid = fork();
	
	printf("Child process PID: %d\n", pid);

	if(pid < 0){
		fprintf(stderr, "Fork failed.\n");
		return 1;
	// child process
	} else if(pid == 0){
		execlp("/bin/ls","ls",NULL);
	} else {
		//parent process; parent will wait for child to complete
		printf("Child process PID: %d\n", pid);
		wait(NULL);
		printf("Child complete\n");
	}
	return 0;
}
