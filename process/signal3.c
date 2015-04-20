#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

static void sig_chld(int);

int main(){
	pid_t pid;
	if(signal(SIGCHLD,sig_chld)==SIG_ERR){
		perror("signal error");
		exit(1);
	}

	if((pid=fork())<0){
		perror("fork error");
	}else if(pid==0){  /* child */
		sleep(2);
		_exit(0);
	}

	pause(); /* parent */
	exit(0);
}

static void sig_chld(int signo){
	pid_t pid;
	int status;
	printf("SIGCHLD received\n");

	if(signal(SIGCHLD,sig_chld)==SIG_ERR) /* reestablish handler */
		perror("signal error");
	if((pid=wait(&status))<0)  /* fetch child status */
		perror("wait error");

	printf("pid=%d\n",pid);

}
