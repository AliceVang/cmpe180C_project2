#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig){
	exit(5);
}

int main(){
	pid_t pid;

	// fork a child process
	pid = fork();

	// parent ignores signal
	signal(SIGINT, SIG_IGN);

	if(pid < 0){
		fprintf(stderr, "Error: fork failed.\n");
		return 1;

	// child process
	} else if(pid == 0){
		printf("%d\n", getpid());

		signal(SIGINT, signal_handler);
		if(signal(SIGINT, signal_handler) == SIG_ERR){
			fprintf(stderr, "Error: unable to set signal handler for SIGINT.\n");
			return 1;
		}
		pause();
		exit(5);
	
	// parent process; parent will wait for child to finish	
       	} else {
		int status;
		waitpid(pid, &status, 0);
		if(WIFEXITED(status)){
			printf("childpid=%d, exitstatus=%d\n", pid, WEXITSTATUS(status));
		} else if(WIFSIGNALED(status)){
			fprintf(stderr,"Error: child terminated by signal %d.\n",WTERMSIG(status));
		}
		
	}
	return 0;
}
