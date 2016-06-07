/*

Ping-pong. Two processes will play the ping-pong game.
The first process will generate a random number between 5000 and 15000 that will be send to the other process.
This process will subtract a random value (between 50 and 1000) and will send the number back,
The chat between the processes will be implemented using pipe channels.
The game ends when the value is below zero.
Each process will print the received value. 

*/

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

	srand(time(NULL));

	int child = fork(); //creating the child process
	
	//child process
	if(child == 0) {	
		if( close(c2p[0]) == -1) printf("close error - c2p read");
		if( close(p2c[1]) == -1) printf("close error - p2c write");		
	
		while(1) {
			read(p2c[0], &number, sizeof(int));      //reading number from parent
			printf("S. received number: %d\n", number);      
			n = rand() % 1000 + 50;      
			number = number - n;         //subtracting a random number
			if(number < 0)               // if the result < 0, then exit
				break;     
			write(c2p[1], &number, sizeof(int));   //otherwise send the number back to the father
		}

		//closing pipes
		if( close(p2c[0]) == -1) printf("close error - p2c read");
		if( close(c2p[1]) == -1) printf("close error - c2p write");
		exit(0);

	}
	// error handling
	if( child == -1){
		perror("Error at forking");
		exit(-1);
	}	

	else {     //parent process
		if( close(c2p[1]) == -1) printf("close error - c2p write");
		if( close(p2c[0]) == -1) printf("close error - p2c read");

		number = rand() % 10000 + 5000; 	//generating a random number and sending it to child
		printf("Generated number is: %d\n", number);
		write(p2c[1], &number, sizeof(int));
	
		while(1){
			read(c2p[0], &number, sizeof(int));   //reading number from child process
			printf("F. received number is: %d\n", number);
			n = rand() % 1000 + 50;
			number = number - n;    //subtracting a random number from it 
			if(number < 0) 
				break;
			write(p2c[1], &number, sizeof(int));	//sending it back to child
			}		
		
		if( close(c2p[0]) == -1) printf("close error - c2p read");
		if( close(p2c[1]) == -1) printf("close error - p2c write");
		wait(0);
	}
	
	printf("Last number is: %d\n", number);

	return 0;
}
	
