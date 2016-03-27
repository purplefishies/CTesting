#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct _thread {
    pthread_attr_t *attr;
    pthread_t _th;
    void *(*get)();
    int (*cancel)();
} Thread;

Thread *NewThread( pthread_attr_t *attr, void *(*work)( void *), void *args ) {
    Thread *tmp = (Thread*)malloc(sizeof(Thread));
    if ( !tmp )
        return tmp;
    int retval  = pthread_create( &tmp->_th, attr, work, args );
    if ( !retval ) {
        free(tmp);
        tmp = NULL;
    }
    
    return tmp;
}

/* NewThread( NULL, calculateValue, {} )->get(); */


int main(int argc, char *argv ) 
{
   

    printf("Hello there\n");
}











