#include <stdio.h>
#include "Employee.h"
#include "Worker.h"

int
main(int argc, char *argv ) {
    Employee *nshape;
    Worker *worker = new_Worker("Jimi","Damon", 112 );
    printf("First: %s\n", worker->firstName(worker) );
    printf("Last: %s\n", worker->lastName(worker) );
    printf("Worked since: %d\n", worker->numberYears(worker ) );
    printf("Repr: %s\n", worker->toStr(worker) );
    printf("Bonus: %f\n", worker->bonus( worker, 2.1 ));
}
