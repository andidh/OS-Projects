#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define R 0
#define W 1

int main() {
	int a[4] = {1,2,3,4};
	int a2p[2];
	int b2p[2];

	pipe(a2p);
	pipe(b2p);

	if( fork() == 0) {	//child a

		a[0] += a[1];
		write(a2p[W], &a[0], sizeof(int));

		close(a2p[R]); close(a2p[W]);
		close(b2p[R]); close(b2p[W]);
		exit(0);
	}

	if (fork() == 0) {   //child b
		a[2] += a[3];

		write(b2p[W], &a[2], sizeof(int));
		close(a2p[R]); close(a2p[W]);
		close(b2p[R]); close(b2p[W]);
		exit(0);
	}


wait(0);
wait(0);

read(a2p[R], &a[0], sizeof(int));
read(b2p[R], &a[2], sizeof(int));


close(a2p[R]); close(a2p[W]);
close(a2p[R]); close(b2p[W]);

a[0] += a[2];

printf("Sum 1+2+3+4 is %d\n", a[0]);

	return 0;
}
