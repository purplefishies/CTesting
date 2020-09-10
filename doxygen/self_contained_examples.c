#include <stdio.h>


int main(int argc, char *argv[] )
{
    int a, r;
    
    init_logging();    
    
    //! <!-- [logging request_loop_start] -->
    r = pthread_create(&thread_id , NULL, process_requests , bus );
    if ( r ) {
        fprintf(stderr, "Error creating SDBus request processor: %s\n",strerror(-r));
        goto finish;
    }
    //! <!-- [logging request_loop_start] -->
    

    /**
     * @section Foo
     * @brief This is somet stuff here
     * @section Main section
     * @brief Some things go in here include...
     * examples
     * @snippet self_contained_examples.c logging request_loop_start
     */



}
