#include <stdio.h>
#include <unistd.h>
#include<pthread.h>

pthread_mutex_t mt1, mt2;

// global variable 
int ok = 0;

//function passed to first thread
void* first(void* param){
	int i;
	for(i =0  ; i<10 ;i++)
	{
		pthread_mutex_lock(&mt1);
		printf("First thread: %d\n", (int)pthread_self());
		pthread_mutex_unlock(&mt2);
	}
	return NULL;
}

//function passed to second thread
void* second(void* param) {
	int i;
	for( i = 0; i<10; i++) {
		pthread_mutex_lock(&mt2);
		printf("Second thread: %d\n", (int)pthread_self());
		pthread_mutex_unlock(&mt1);
	}
	return NULL;
}

int main(){

	pthread_t t1, t2;
	int ret1, ret2;

	// initializing the mutex	
	pthread_mutex_init(&mt1, NULL);
	pthread_mutex_init(&mt2, NULL);

	pthread_mutex_lock(&mt2);

	//creating the 2 threads
	ret1 = pthread_create(&t1, NULL, first, NULL);
	ret2 = pthread_create(&t2, NULL, second, NULL);

	 if(ret1){
		printf("Error at creating thread: %d\n", ret1);
	}

	if( ret2 ){
		printf("Error at creating thread: %d\n", ret2);
	}


	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mt1);
	pthread_mutex_destroy(&mt2);

	return 0;
}

