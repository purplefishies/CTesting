#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <iostream>

class Thread { 
public:
    Thread( pthread_attr_t *attr, void *(*work)( void *), void *args );
    Thread( void *(*work)( void *), void *args );
    void *Get();
    int Cancel();
private:

    pthread_attr_t *attr;
    pthread_t _th;

};

Thread::Thread( pthread_attr_t *attr, void *(*work)( void *), void *args ) : attr(attr)
{
    int retval  = pthread_create( &this->_th, this->attr, work, args );
    if ( retval != 0 ) 
        throw std::string("Can't creat thread\n");
}

Thread::Thread( void *(*work)( void *), void *args ) : attr(attr)
{
    int retval  = pthread_create( &this->_th, NULL, work, args );
    if ( retval != 0 ) 
        throw std::string("Can't creat thread\n");
}

void *Thread::Get() { 
    void *retval;
    pthread_join(this->_th, &retval );
    return retval;
}

int Thread::Cancel() {
    return pthread_cancel( this->_th );
}

void *sleep_awhile(void *in ) {
    int input = *(int*)in;
    static int tmp = input / 3000;
    usleep(input);
    printf("Done sleeping\n");
    return &tmp;
}

int main(int argc, char *argv[] ) 
{
    int tosleep = 3000000;

    // Thread tmp( NULL, sleep_awhile, &tosleep );
    // Thread *tmp = new Thread(NULL, sleep_awhile, &tosleep );
    // tmp->Get();
    auto func = [] (int val ) { std::cout << "Hello world"; };

    printf("Value: %d\n", *(int*)Thread(sleep_awhile,&tosleep).Get());
    //
    // 
    // 

    // (new Thread(NULL,sleep_awhile,&tosleep))->Get();

    printf("Hello there\n");
}











