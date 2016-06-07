#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define R 0
#define W 1 

int main(){

	int a2b[2], b2a[2];
	pipe(a2b); pipe(b2a);

	int num;
	printf("Enter number: ");
	scanf("%d", &num);

	//forking
	switch(fork()) {

		//error handling
		case -1:
			printf("Error at forking\n!");
			break;


		//child
		case 0:
			close(a2b[W]); close(b2a[R]);
			
			while(1){
			read(a2b[R], &num, sizeof(int));
				if( num % 2 == 0) {
					num = num / 2;
					printf("S number: %d\n", num);
					write(b2a[W], &num, sizeof(int));
				}
				else {
					printf("DONE");
					break;
					}
			}

			close(a2b[R]); close(b2a[W]);
			exit(0);
			
			break;


		default:
			close(a2b[R]); close(b2a[W]);
	
			write(a2b[W], &num, sizeof(int));
			while(1){
				read(b2a[R], &num, sizeof(int));
				if(num / 3 != 0){
					num = num /3;
					printf("F. number: %d\n", num);
					write(a2b[W], &num, sizeof(int));
				} else {
					printf("Done");
					break;
					}
				}
			close(a2b[W]); close(b2a[R]);
			wait(0);
			break;

		}


		return 0;

		}
