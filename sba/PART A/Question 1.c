#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

#define childno 3
#define buffer_s 256

int main(void) {
	
	int pipefd[childno][3];
	pid_t ch[childno];
	void sigint_h(int sig);
	char s[200];

	for (int c = 0; c < childno; c++){
		if (pipe(pipefd[c]) == -1){
			perror("Pipe failed");
			exit(1);
		}
	}

	for (int c = 0; c<childno; c++){
		pid_t child = fork();
		if (child < 0){
			perror ("Fork failed");
			exit(1);
		}
		else if (child == 0){
			close(pipefd[c][1]);
			char buf[buffer_s];
			size_t bytesRead = read(pipefd[c][0], buf, buffer_s);
			if (bytesRead > 0) {
				printf ("\nChild %d (PID: %d) receive: %s \n", c+1, getpid(), buf);
			}
			close (pipefd[c][0]);
			exit(0);
		}
		else {
			ch[c] = child;
		}
	}

	for (int i =0; i<childno; i++){
		close(pipefd[i][0]);

		char message[buffer_s];
		snprintf(message, buffer_s, "\nHello from parent (PID: %d) to child %d \n", getpid(), i+1);
		write(pipefd[i][1], message, buffer_s);
		close(pipefd[i][1]);
	}

	for (int i = 0; i<childno; i++){
		waitpid(ch[i], NULL, 0);
	}

	if (signal(SIGINT, sigint_h) == SIG_ERR){
		perror ("signal");
		exit(1);
	}
	
	printf ("Enter a string: \n");

	if (fgets(s, sizeof s, stdin) == NULL)
		perror ("gets");
	else
		printf("You enter: %s\n",s);

	return 0;
}
void sigint_h(int sig)
{
	printf("Not this time!!!\n");
}
