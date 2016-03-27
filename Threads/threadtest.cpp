#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <stack>
#include <list>
#include <tuple>

template <class R,class A>
class Thread { 
public:

    Thread( pthread_attr_t *attr, R *(*work)( A ), A args );
    Thread( R (*work)( A), A args );
    R Get();
    int Cancel();
    ~Thread() { this->Cancel();};
private:
    static void * wrap(void * This) {
        Thread<R,A> *THIS = (Thread<R,A>*)This;
        THIS->retval = THIS->work( THIS->args  );
        return &THIS->retval;
    }
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    R (*work)(A args );
    A args;
    R retval;
    pthread_attr_t *attr;
    pthread_t _th;

};

template <class R,class A>
Thread<R,A>::Thread( R (*work)( A ), A args ) :  args(args), retval(-1)
{
    this->work = work;
    pthread_mutex_init( &this->mutex, NULL );
    pthread_cond_init( &this->cond , NULL );
    int retval  = pthread_create( &this->_th, NULL, wrap, this  );
    if ( retval != 0 ) 
        throw std::string("Can't creat thread\n");
}

template <class R,class A>
R Thread<R,A>::Get() { 
    R retval;
    void *tval;
    // pthread_cond_wait( &this->cond , &this->mutex );
    pthread_join(this->_th, &tval );
    retval = *(R*)tval;
    return retval;
}

template <class R,class A>
int Thread<R,A>::Cancel() {
    return pthread_cancel( this->_th );
}

int test_sleep( int val ) {
    printf("About to sleep\n");
    usleep(val);
    printf("Done sleeping with value %d\n", val);
    return 42 + val;
}

using namespace std;
int main(int argc, char *argv[] ) 
{
    int tosleep = 3000000;

    auto func = [] (int val ) { 
        std::cout << "Hello world\n"; 
        for ( int i = 0; i < val ; i ++ ) { 
            if ( i % 10000 == 0 ) {
                std::cout << i << "\n";
            }
        }
        usleep(val);
        return val + 52;
    };

    printf("Trying it out : %d\n", test_sleep(200));
    Thread<int,int> **ary = (Thread<int,int>**)malloc(3*sizeof(Thread<int,int>*));

    ary[0] = ( new Thread<int,int>( test_sleep, 300000 ));
    ary[1] = ( new Thread<int,int>( test_sleep, atoi(argv[1] )));
    ary[2] = ( new Thread<int,int>( func, 42 ));
    int counter = 0;
    printf("Value\n\n\n");
    printf("Value\n");
    sleep(1);
    for ( int i = 0; i <= 2 ; i ++ ) {
        printf("Value was %d\n", ary[i]->Get() );
    }
    auto sumnums = []( std::tuple<int,int> start_stop ) -> int { 
            printf("start: %d, stop: %d\n", std::get<0>(start_stop), std::get<1>( start_stop ));
            int sum = 0;
            for( int i= std::get<0>(start_stop); i <= std::get<1>( start_stop ) ; i ++ )
                sum += i;
            printf("Sum was %d\n",sum);
            return sum;
    };

    auto fn = [sumnums](int n) -> long { 
        Thread<int,std::tuple<int,int>> t1( sumnums, std::tuple<int,int>(0,n) );
        Thread<int,std::tuple<int,int>> t2( sumnums, std::tuple<int,int>(n+1,2*n) );

        // Goal is just
        // retval = seq(0,2*n,n).map { Thread<int,>...() }.map{ _.Get() }.sum();
        
        return (long) t1.Get() + (long)t2.Get();
    };

    printf("Val was %ld\n", fn(1000000));

}











