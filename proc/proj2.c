#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main() {

	int p2c[2], c2p[2], number, n;

	if(pipe(p2c) == -1){				//creating parent to child pipe
		perror("Error at pipe");
		exit(-1);
	}
	if(pipe(c2p) == -1){				//creating child to parent pipe
		perror("Error at pipe");
		exit(-1);
	}



	int child = fork(); //creating the child process

	if(child == 0) {	
		if( close(c2p[0]) == -1) printf("close error - c2p read");
		if( close(p2c[1]) == -1) printf("close error - p2c write");		
	
		while(1) {
			read(p2c[0], &number, sizeof(int));
			printf("S. received number: %d\n", number);
			n = rand() % 1000 + 50;
			number = number - n;
			if(number < 0)
				break;
			printf("S. sends number: %d\n", number);
			write(c2p[1], &number, sizeof(int));
		}

		if( close(p2c[0]) == -1) printf("close error - p2c read");
		if( close(c2p[1]) == -1) printf("close error - c2p write");
		exit(0);
	} if( child == -1){
		perror("Error at forking");
		exit(-1);
	}	
	else {
		if( close(c2p[1]) == -1) printf("close error - c2p write");
		if( close(p2c[0]) == -1) printf("close error - p2c read");

		number = rand() % 10000 + 5000;		
		printf("Generated number is: %d\n", number);
		write(p2c[1], &number, sizeof(int));
	
		while(1){
			read(c2p[0], &number, sizeof(int));
			printf("F. received number is: %d\n", number);
			n = rand() % 1000 + 50;
			number = number - n;
			if(number < 0)
				break;
			printf("F. sends number: %d\n", number);
			write(p2c[1], &number, sizeof(int));
			}		
		
		if( close(c2p[0]) == -1) printf("close error - c2p read");
		if( close(p2c[1]) == -1) printf("close error - p2c write");
		wait(0);
	}
	
	printf("Last number is: %d\n", number);

	return 0;
}
	
