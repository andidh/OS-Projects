#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

#define r 0
#define w 1

int main() {

	int p2c[2], c2p[2];
	int n;
	int new;

	if(pipe(p2c)==-1){
		perror("Error at pipe p2c");
		exit(-1);}

	if( pipe(c2p)==-1){
		perror("Error at pipe c2p");
		exit(-1);}

	printf("Enter a number: ");
	scanf("%d", &n);


	switch(fork()) {


		case -1:
			printf("Error at forking");
			exit(-1);

		case 0:
			close(p2c[w]); close(c2p[r]);
			read(p2c[r], &n, sizeof(int));

			for(int i=0; i<n; i++) {
				new =  rand() % 100;
				write(c2p[w], &new, sizeof(int));
			}
			close(p2c[r]); close(c2p[w]);
			exit(0);



		default:
			close(p2c[r]); close(c2p[w]);

			write(p2c[w], &n, sizeof(int));
			for(int i =0 ;i <n; i++){
				read(c2p[r], &new, sizeof(int));
				printf("%d\n", new);
				}
			close(p2c[w]); close(c2p[r]);
			wait(0);
		}


	return 0;

	}