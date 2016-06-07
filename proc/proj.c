#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>



int main() {

	int p2c[2], c2p[2], number, n;

	pipe(c2p);
	pipe(p2c);

//	number = rand() %10000 + 5000;
	printf("Generated number is : %d\n", number);

	if(fork() == 0){

		while( number > 0){
			

			printf("Child process\n");
			read(p2c[0], &number, sizeof(int));
			printf("Received numberL %d\n", number);
			n = rand() % 1000 + 50;
			number = number - n;
			write(c2p[1], &number, sizeof(int));
		}
		close(c2p[0]); close(c2p[1]);
		close(p2c[0]); close(p2c[1]);
	} else {
		number = rand() %10000 + 5000;
		while(number > 0){
			write(p2c[1], &number, sizeof(int));
			printf("Father process\n");
			read(c2p[0], &number, sizeof(int));
			printf("Parent received number: %d\n", number);
			n = rand() %10000 + 5000;
			number = number - n;
			write(p2c[1], &number, sizeof(int));
		}	
		close(p2c[0]); close(p2c[1]);
		close(c2p[0]); close(c2p[1]);
		wait(NULL);
	}
	printf("Final number: %d\n", number);
	
	return 0;
}
		
