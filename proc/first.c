#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(){
	int p;
	p = fork();
	
	if (p==-1){
		printf("Error at forking\n");
		exit(1);
	}
	if(p==0){
		printf("I am child : pid: %d, parent pid: %d\n", getpid(), getppid());
		exit(0);
	}
	else {
		printf("I am parent!");
		p = fork();
		if (p== -1){
			perror("Forking error");
			exit(1);}
	}
	return 0;
	}
