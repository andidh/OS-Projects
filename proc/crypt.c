#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define R 0
#define W 1
char filename[100], buffer[10000];

int main(){

	int pipefd[2];
	scanf("%s", filename);
	freopen(filename, "r", stdin);
	fread(buffer, 1, 1000, stdin);
	pipe(pipefd);

	if(fork() == 0) {
		close(pipefd[W]);

		char buff;
		printf("The child writes");
		while(read(pipefd[0], &buff, 1) > 0)
				write(STDOUT_FILENO, &buff, 1);
		printf("The child has read!");

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
	}
	else {
	
		close(pipefd[0]);
		write(pipefd[1], buffer, strlen(buffer));
		close(pipefd[1]);
		printf("The parent has finished writing");
		wait(NULL);
		exit(EXIT_SUCCESS);
		}

	return 0;
}
