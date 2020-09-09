#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 


int counter; 
pthread_mutex_t lock; 

void* trythis(void* arg) 
{ 
	pthread_mutex_lock(&lock); 

	unsigned long i = 0; 
	counter += 1; 
	printf("\n Job %d has started\n", counter); 

	for (i = 0; i < (0xFFFF); i++) 
		; 

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 

	return NULL; 
} 

int main(int argc, char *argv[]) 
{ 
	int i = 0 ;
	int error; 
        /* pthread_t tid[5];  */
        pthread_t *tid = NULL;
        if (argc != 2 ) {
          fprintf(stderr,"Usage: %s NUMBER\n", argv[0] );
          exit(1);
        }
        int num = atoi(argv[1]);
        tid = (pthread_t*)malloc(num*sizeof(pthread_t));


	if (pthread_mutex_init(&lock, NULL) != 0) { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	while (i < num) { 
		error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
		if (error != 0) 
			printf("\nThread can't be created :[%s]", 
				strerror(error)); 
		i++; 
	} 

        for ( int i = 0; i < num; i++ ) {
          pthread_join(tid[i],NULL);
        }

	pthread_mutex_destroy(&lock); 

	return 0; 
} 

